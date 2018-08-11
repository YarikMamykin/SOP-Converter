#include "IcoFoamManager.h"
using FileManager = configuration::FileManager;
using Parser = configuration::Parser;
using LogManager = logging::Logger;

management::IcoFoamManager::IcoFoamManager() :
    QObject(),
    icoFoamExecutor(new configuration::OFCommandExecutor(QStringList("icoFoam"), FileManager::getInstance()->getWorkDir())),    
    addedSyncResultsCounter(0),
    resultsCount(Parser::getInstance()->getMapsCount()),
    icoFoamThread(new QThread)
{
    LogManager::getInstance()->log("IcoFoamManager constructed");
}

management::IcoFoamManager::~IcoFoamManager()
{
    icoFoamExecutor.reset();
    icoFoamThread.reset();
    LogManager::getInstance()->log("IcoFoamManager destroyed");
}

management::IcoFoamManager* management::IcoFoamManager::getInstance()
{
    static IcoFoamManager instance;
    return &instance;
}

void management::IcoFoamManager::addSyncResult(int syncId, bool result)
{
    LogManager::getInstance()->log("Adding synchronize result");
    LogManager::getInstance()->log(QString("%1 -> %2").arg(syncId).arg(boolToString(result)));
    addedSyncResultsCounter++;
    if(addedSyncResultsCounter != resultsCount)
    { return; }
    else
    {
        LogManager::getInstance()->log("Files synced!");
        // here we start icoFoam app in separate thread
        // to have full control on it.
    }
}

void management::IcoFoamManager::clearCounter()
{
    addedSyncResultsCounter = 0;
    LogManager::getInstance()->log("addedSyncResultsCounter cleared");
}

