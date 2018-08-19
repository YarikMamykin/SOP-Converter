#include "IcoFoamManager.h"
#include <QDebug>
using FileManager = configuration::FileManager;
using Parser = configuration::Parser;
using LogManager = logging::Logger;
using LogDirection = logging::LogDirection;

/* ---------------------------------------------------------------------- */
/* -- IcoFoamManager -- */
/* ---------------------------------------------------------------------- */
std::atomic<bool> management::IcoFoamManager::useReadLineTimeout;
std::atomic<bool> management::IcoFoamManager::executorThreadFinished;

management::IcoFoamManager::IcoFoamManager() :
    QObject(),
    resultsCount(Parser::getInstance()->getMapsCount()),
    syncTimeoutMax(5000),          // in ms
    waitForReadyReadTimeout(1500), // in ms
    timer(new QTimer),
    elapsedTime(new QElapsedTimer),
    syncResults(new std::map<int, bool>()),
    icoFoamStarted(false),
    stopExecutionConn()
{
    QObject::connect(timer.get(),
                     SIGNAL(timeout()),
                     this,
                     SLOT(handleSyncFail()));
    QObject::connect(this,
                     &IcoFoamManager::startExecution,
                     this,
                     &IcoFoamManager::doProcessStandartOut, Qt::DirectConnection);

    timer->setInterval(syncTimeoutMax);
    useReadLineTimeout.store(true);
    LogManager::getInstance()->log("IcoFoamManager constructed");
}

management::IcoFoamManager::~IcoFoamManager()
{
    timer.reset();
    elapsedTime.reset();
    syncResults->clear();
    syncResults.reset();
    LogManager::getInstance()->log("IcoFoamManager destroyed");
}

management::IcoFoamManager* management::IcoFoamManager::getInstance()
{
    static IcoFoamManager instance;
    return &instance;
}

void management::IcoFoamManager::startTimer()
{
    timer->start();
    elapsedTime->start();
    emit clearConsole();
    LogManager::getInstance()->log("IcoFoamManager Timer started");
}

void management::IcoFoamManager::addSyncResult(int syncId, bool result)
{
    LogManager::getInstance()->log("Adding synchronize result");
    LogManager::getInstance()->log(QString("%1 -> %2").arg(syncId).arg(boolToString(result)));
    syncResults->insert(std::pair<int, bool>(syncId, result));
    if(syncResults->size() != resultsCount)
    { /*timer->start();*/ return; }
    else
    {
        timer->stop();
        LogManager::getInstance()->log(QString("FILES SYNCED! Elapsed time = %1 ms").arg(elapsedTime->elapsed()));

        emit startExecution();

        LogManager::getInstance()->log("EXECUTION STARTED!");
    }
}

void management::IcoFoamManager::clearFlags()
{
    syncResults->clear();
    LogManager::getInstance()->log("syncResults cleared");
}

void management::IcoFoamManager::handleSyncFail()
{
    timer->stop();

    LogManager::getInstance()->log(QString("Elapsed time = %1 ms").arg(elapsedTime->elapsed()));
    LogManager::getInstance()->log(QString("Sync failed! Next files handled (%1/%2):").arg(syncResults->size()).arg(resultsCount));
    for(auto e : *syncResults.get())
    {
        LogManager::getInstance()->log(QString("%1 synced --> %2").
                                       arg(Parser::parserIdToString(static_cast<ParserId>(e.first))).
                                       arg(e.second));
    }

}

QMetaObject::Connection& management::IcoFoamManager::getStopExecutionConn()
{
    return stopExecutionConn;
}

void management::IcoFoamManager::doProcessStandartOut()
{
    this->blockSignals(true);
    LogManager::getInstance()->log("doProcessStandartOut\n\nEstablishing connection to file icoFoam.log ...");

    management::IcoFoamManager::useReadLineTimeout.store(true);

    QThread* executorThread = new QThread;
    QThread* processorThread = new QThread;

    /* icoFoam process filereader init */
    IcoFoamOutputProcessor* processor = new IcoFoamOutputProcessor;

    QObject::connect(processor, SIGNAL(finished()), processorThread, SLOT(quit()));
    QObject::connect(processor, SIGNAL(finished()), processor, SLOT(deleteLater()));
    QObject::connect(processorThread, SIGNAL(finished()), processorThread, SLOT(deleteLater()));
    QObject::connect(processorThread, SIGNAL(started()), processor, SLOT(observe()));
    QObject::connect(processorThread, &QThread::started, []()
    {
        LogManager::getInstance()->log("processorThread started");
    });
    QObject::connect(processorThread, &QThread::finished, []()
    {
        LogManager::getInstance()->log("processorThread finished");
    });

    /* icoFoam process init */
    QProcess* executor = new QProcess;
    executor->setProgram("icoFoam");
    executor->setWorkingDirectory(FileManager::getInstance()->getWorkDir().get()->path());
    executor->setReadChannelMode(QProcess::MergedChannels);
    executor->setStandardOutputFile(FileManager::getInstance()->getIcoFoamLogFile().get()->fileName());
    executor->open(QIODevice::Truncate|QIODevice::ReadWrite|QIODevice::Unbuffered);


    stopExecutionConn = QObject::connect(this, &IcoFoamManager::stopExecution, [executor, executorThread, this]()
    {
        this->blockSignals(true);

        LogManager::getInstance()->log("Stopping icoFoam");
        executor->kill();
        executor->waitForFinished(1500);
        executorThread->quit();
        QProcess::execute("killall icoFoam");
        LogManager::getInstance()->log("icoFoam process killed!");
        management::IcoFoamManager::useReadLineTimeout.store(false);
        QObject::disconnect(this->getStopExecutionConn());
//        IcoFoamManager::executorThreadFinished.store(true);
        this->blockSignals(false);
    });
    QObject::connect(executorThread, SIGNAL(finished()), executorThread, SLOT(quit()), Qt::QueuedConnection);
    QObject::connect(executorThread, SIGNAL(finished()), executorThread, SLOT(deleteLater()), Qt::QueuedConnection);
    QObject::connect(executorThread, SIGNAL(finished()), executor, SLOT(kill()), Qt::QueuedConnection);
    QObject::connect(executorThread, SIGNAL(finished()), executor, SLOT(deleteLater()), Qt::QueuedConnection);

    QObject::connect(executor, static_cast<void (QProcess::*)(int)>(&QProcess::finished), [executor, executorThread, this](int)
    {
        management::IcoFoamManager::useReadLineTimeout.store(false);
        executorThread->quit();
        LogManager::getInstance()->log(QString("icoFoam process finished! (%1)").arg(boolToString(executor->atEnd())));
        if(executor->atEnd())
        {
            QObject::disconnect(this->getStopExecutionConn());
            emit this->requestEnableUi();
        }
        IcoFoamManager::executorThreadFinished.store(true);
    });

    QObject::connect(executorThread, &QThread::finished, []() { LogManager::getInstance()->log("executorThread finished"); });
    QObject::connect(executorThread, &QThread::started, [this, executor, processorThread, waitTimeout=waitForReadyReadTimeout]()
    {
        executor->start();
        IcoFoamManager::executorThreadFinished.store(false);
        executor->waitForReadyRead(waitTimeout);
        processorThread->start();
    });
    QObject::connect(executorThread,  &QThread::started, []() { LogManager::getInstance()->log("executorThread started"); });

    executor->moveToThread(executorThread);
    processor->moveToThread(processorThread);

    executorThread->start();
    this->blockSignals(false);
}

/* ---------------------------------------------------------------------- */
/* -- IcoFoamOutputProcessor -- */
/* ---------------------------------------------------------------------- */

management::IcoFoamOutputProcessor::IcoFoamOutputProcessor() :
    readLineTimeout(25) // in ms
{
    LogManager::getInstance()->log("IcoFoamOutputProcessor constructed");
}

management::IcoFoamOutputProcessor::~IcoFoamOutputProcessor()
{
    LogManager::getInstance()->log("IcoFoamOutputProcessor destroyed");
}

void management::IcoFoamOutputProcessor::operator ()()
{
    std::shared_ptr<QFile> icoFoamOut = FileManager::getInstance()->getIcoFoamLogFile();
    if(!icoFoamOut.get()->open(QIODevice::ReadOnly|QIODevice::Text|QIODevice::Unbuffered))
    {
        LogManager::getInstance()->log("Can't open icoFoam.log!");
        return;
    }

    LogManager::getInstance()->log("\n\n### - icoFoam.log START - ###");
    QString buffer;
    while(!icoFoamOut.get()->atEnd() || !IcoFoamManager::executorThreadFinished.load())
    {
        if(management::IcoFoamManager::useReadLineTimeout.load())
        { QThread::msleep(readLineTimeout); }
        buffer = icoFoamOut.get()->readLine();
        if(buffer != QString("\n") && !buffer.isEmpty() && !buffer.isNull())
            LogManager::getInstance()->log(buffer.trimmed(), LogDirection::console);
    }

    icoFoamOut.get()->close();
    LogManager::getInstance()->log("### - icoFoam.log END - ###\n\n");
}

void management::IcoFoamOutputProcessor::observe()
{
    (*this)();
    emit finished();
}
