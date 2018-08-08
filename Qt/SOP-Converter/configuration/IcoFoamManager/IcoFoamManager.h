#ifndef ICOFOAMMANAGER_H
#define ICOFOAMMANAGER_H

#include <QThread>
#include <memory>
#include "../../configuration/OFCommandExecutor/OFCommandExecutor.h"
#include "../../configuration/ClientManager/ClientManager.h"

namespace configuration
{

class IcoFoamManager final : public QObject
{
private:
    explicit IcoFoamManager();
    explicit IcoFoamManager(const IcoFoamManager&) = delete;
    virtual ~IcoFoamManager();
public:
    static IcoFoamManager* getInstance();
    void startExecution();
    void stopExecution();
private:
    std::unique_ptr<configuration::OFCommandExecutor> icoFoamExecutor;
    std::unique_ptr<configuration::ClientManager> clientManager;
};

}
#endif // ICOFOAMMANAGER_H
