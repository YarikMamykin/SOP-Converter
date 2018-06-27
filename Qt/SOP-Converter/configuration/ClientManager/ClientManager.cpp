#include "ClientManager.h"
#include "../../logging/Logger/Logger.h"
using LogManager = logging::Logger;

configuration::ClientManager::ClientManager() :
    selectFileDialog()
{
    LogManager::getInstance()->log("ClientManager constructed");
}

configuration::ClientManager::~ClientManager()
{
    LogManager::getInstance()->log("ClientManager destructed");
}
