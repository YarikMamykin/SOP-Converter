#ifndef ICOFOAMMANAGER_H
#define ICOFOAMMANAGER_H

#include <QObject>
#include <QThread>
#include <QStringList>
#include <memory>
#include "../../configuration/OFCommandExecutor/OFCommandExecutor.h"
#include "../../configuration/Parser/Parser.h"
#include "../../logging/Logger/Logger.h"

namespace management
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
    void clearCounter();
private:
    // clientManager cannot be a member of static class!!! --> causes core dump
    std::unique_ptr<configuration::OFCommandExecutor> icoFoamExecutor;    
    int addedSyncResultsCounter;
    const int resultsCount;
    std::unique_ptr<QThread> icoFoamThread;
};

}
#endif // ICOFOAMMANAGER_H
