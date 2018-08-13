#include "IcoFoamManager.h"
#include <QDebug>
using FileManager = configuration::FileManager;
using Parser = configuration::Parser;
using LogManager = logging::Logger;
using LogDirection = logging::LogDirection;

/* ---------------------------------------------------------------------- */
/* -- IcoFoamManager -- */
/* ---------------------------------------------------------------------- */

management::IcoFoamManager::IcoFoamManager() :
    QObject(),
    resultsCount(Parser::getInstance()->getMapsCount()),
    syncTimeoutMax(5000),          // in ms
    waitForReadyReadTimeout(1000), // in ms
    timer(new QTimer),
    elapsedTime(new QElapsedTimer),
    syncResults(new std::map<int, bool>())
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
    LogManager::getInstance()->log("addedSyncResultsCounter cleared");
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

void management::IcoFoamManager::doProcessStandartOut()
{
    LogManager::getInstance()->log("doProcessStandartOut\n\nEstablishing connection to file icoFoam.log ...");

    QThread* executorThread = new QThread;
    QThread* processorThread = new QThread;

    /* icoFoam process filereader init */
    IcoFoamOutputProcessor* processor = new IcoFoamOutputProcessor;

    QObject::connect(processor, SIGNAL(finished()), processorThread, SLOT(quit()));
    QObject::connect(processor, SIGNAL(finished()), processor, SLOT(deleteLater()));
    QObject::connect(processorThread, SIGNAL(finished()), processorThread, SLOT(deleteLater()));
    QObject::connect(processorThread, SIGNAL(started()), processor, SLOT(observe()));
    QObject::connect(processorThread, &QThread::started, [](){ LogManager::getInstance()->log("processorThread started"); } );
    QObject::connect(processorThread, &QThread::finished, [](){ LogManager::getInstance()->log("processorThread finished"); });

    /* icoFoam process init */
    QProcess* executor = new QProcess();
    executor->setProgram("icoFoam");
    executor->setWorkingDirectory(FileManager::getInstance()->getWorkDir().get()->path());
    executor->setReadChannelMode(QProcess::MergedChannels);
    executor->setStandardOutputFile(FileManager::getInstance()->getIcoFoamLogFile().get()->fileName());


    QObject::connect(executor, static_cast<void (QProcess::*)(int)>(&QProcess::finished), [executorThread](int){executorThread->quit();});
    QObject::connect(executorThread, SIGNAL(finished()), executor, SLOT(deleteLater()));
    QObject::connect(executorThread, SIGNAL(finished()), executorThread, SLOT(deleteLater()));
    QObject::connect(executorThread, &QThread::finished, [](){ LogManager::getInstance()->log("executorThread finished"); });
    QObject::connect(executorThread, &QThread::started, [executor, processorThread, waitTimeout=waitForReadyReadTimeout]()
    {
        executor->start();
        executor->setTextModeEnabled(true);
        executor->waitForReadyRead(waitTimeout);
        processorThread->start();
    });
    QObject::connect(executorThread,  &QThread::started, [](){ LogManager::getInstance()->log("executorThread started"); } );
    QObject::connect(executor, SIGNAL(readyRead()), processorThread, SLOT(start()));

    executor->moveToThread(executorThread);
    processor->moveToThread(processorThread);

    executorThread->start();

}

/* ---------------------------------------------------------------------- */
/* -- IcoFoamOutputProcessor -- */
/* ---------------------------------------------------------------------- */

management::IcoFoamOutputProcessor::IcoFoamOutputProcessor() :
    readLineTimeout(30) // in ms
{
    LogManager::getInstance()->log("IcoFoamOutputProcessor constructed");
}

management::IcoFoamOutputProcessor::~IcoFoamOutputProcessor()
{
    LogManager::getInstance()->log("IcoFoamOutputProcessor destroyed");
}

void management::IcoFoamOutputProcessor::operator ()()
{
//    LogManager::getInstance()->log("Connecting to icoFoam output");
//    QThread::msleep(10000);

    std::shared_ptr<QFile> icoFoamOut = FileManager::getInstance()->getIcoFoamLogFile();
    if(!icoFoamOut.get()->open(QIODevice::ReadOnly|QIODevice::Text))
    {
        LogManager::getInstance()->log("Can't open icoFoam.log!");
        return;
    }

    QString buffer;

    LogManager::getInstance()->log("Reading icoFoam.log file");
    while(!icoFoamOut.get()->atEnd())
    {
        QThread::msleep(readLineTimeout);
        buffer = icoFoamOut.get()->readLine();
        if(buffer != QString("\n"))
            LogManager::getInstance()->log(buffer.trimmed(), LogDirection::console);
    }

    LogManager::getInstance()->log("File closing!");

    icoFoamOut.get()->close();
}

void management::IcoFoamOutputProcessor::observe()
{
    (*this)();
    emit finished();
}
