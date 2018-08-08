#include "IcoFoamManager.h"
using FileManager = configuration::FileManager;
using LogManager = logging::Logger;

configuration::IcoFoamManager::IcoFoamManager() :
    QObject(),
    icoFoamExecutor(new configuration::OFCommandExecutor(QStringList("icoFoam"), FileManager::getInstance()->getWorkDir())),
    clientManager(nullptr),
    syncResults(new std::map<int, bool>())
{
    LogManager::getInstance()->log("IcoFoamManager constructed");
}

configuration::IcoFoamManager::~IcoFoamManager()
{
    icoFoamExecutor.reset();
    clientManager = nullptr;
    syncResults.reset();
    LogManager::getInstance()->log("IcoFoamManager destroyed");
}

configuration::IcoFoamManager* configuration::IcoFoamManager::getInstance()
{
    static IcoFoamManager instance;
    return &instance;
}

void configuration::IcoFoamManager::addSyncResult(int syncId, bool result)
{
    LogManager::getInstance()->log("Adding synchronize result");
    LogManager::getInstance()->log(QString("%1 -> %2").arg(syncId).arg(boolToString(result)));
}

void configuration::IcoFoamManager::setClientManager(std::shared_ptr<configuration::ClientManager> cm)
{
    LogManager::getInstance()->log("IcoFoamManager setClientManager");
    clientManager = cm;
}
