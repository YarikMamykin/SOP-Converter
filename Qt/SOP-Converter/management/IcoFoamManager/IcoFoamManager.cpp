#include "IcoFoamManager.h"
using FileManager = configuration::FileManager;
using Parser = configuration::Parser;
using LogManager = logging::Logger;

management::IcoFoamManager::IcoFoamManager() :
    QObject(),
    icoFoamExecutor(new configuration::OFCommandExecutor(QStringList("icoFoam"), FileManager::getInstance()->getWorkDir())),        
    resultsCount(Parser::getInstance()->getMapsCount()),
    syncTimeoutMax(5000),
    icoFoamThread(new QThread),
    timer(new QTimer),
    elapsedTime(new QElapsedTimer),
    syncResults(new std::map<int, bool>())
{
    QObject::connect(timer.get(),
                     SIGNAL(timeout()),
                     this,
                     SLOT(handleSyncFail()));
    timer->setInterval(syncTimeoutMax);
    LogManager::getInstance()->log("IcoFoamManager constructed");
}

management::IcoFoamManager::~IcoFoamManager()
{
    icoFoamExecutor.reset();
    icoFoamThread.reset();
    timer.reset();
    elapsedTime.reset();
    syncResults->clear(); syncResults.reset();

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
        LogManager::getInstance()->log("Starting icoFoam! Console will be cleared in 3 seconds!");

        // here we start icoFoam app in separate thread
        // to have full control on it.
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
