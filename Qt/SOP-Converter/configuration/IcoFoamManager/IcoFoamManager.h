#ifndef ICOFOAMMANAGER_H
#define ICOFOAMMANAGER_H

#include <QObject>
#include <QThread>
#include <QStringList>
#include <memory>
#include <map>
#include "../../configuration/OFCommandExecutor/OFCommandExecutor.h"
#include "../../configuration/Parser/Parser.h"
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
    // TODO: Define all necessary signals and connect them in ClientManager constructor
public slots:
    void addSyncResult(int,bool);
private:
    // clientManager cannot be a member of static class!!! --> causes core dump
    std::unique_ptr<configuration::OFCommandExecutor> icoFoamExecutor;
    std::unique_ptr<std::map<int, bool>> syncResults;
    int appliableSyncResultsCounter;
};

}
#endif // ICOFOAMMANAGER_H
