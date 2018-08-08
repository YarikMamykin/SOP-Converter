#ifndef ICOFOAMMANAGER_H
#define ICOFOAMMANAGER_H

#include <QObject>
#include <QThread>
#include <QStringList>
#include <memory>
#include <map>
#include "../../configuration/OFCommandExecutor/OFCommandExecutor.h"
#include "../../configuration/ClientManager/ClientManager.h"
#include "../../configuration/FileManager/FileManager.h"
#include "../../logging/Logger/Logger.h"

namespace configuration
{

class IcoFoamManager final : public QObject
{
    Q_OBJECT
private:
    explicit IcoFoamManager();
    explicit IcoFoamManager(const IcoFoamManager&) = delete;
    virtual ~IcoFoamManager();
public:
    static IcoFoamManager* getInstance();
//    void startExecution();
//    void stopExecution();
public slots:
    void addSyncResult(int,bool);
    void setClientManager(std::shared_ptr<configuration::ClientManager> cm);
private:
    std::unique_ptr<configuration::OFCommandExecutor> icoFoamExecutor;
    std::shared_ptr<configuration::ClientManager> clientManager;
    std::unique_ptr<std::map<int, bool>> syncResults;
};

}
#endif // ICOFOAMMANAGER_H
