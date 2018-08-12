#ifndef ICOFOAMMANAGER_H
#define ICOFOAMMANAGER_H

#include <QObject>
#include <QThread>
#include <QTimer>
#include <QElapsedTimer>
#include <QStringList>
#include <QTextStream>
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
signals:
    void startExecution(); // must be used when Ui->file synchronizing is omitted. (Ui had no changes)
    void stopExecution();
    void clearConsole();
    void processStandartOut();
    // TODO: Define all necessary signals and connect them in ClientManager constructor
public slots:
    void startTimer();
    void addSyncResult(int,bool);
    void clearFlags();
private slots:
    void handleSyncFail();
    void doProcessStandartOut();
private:
    // clientManager cannot be a member of static class!!! --> causes core dump
    std::unique_ptr<configuration::OFCommandExecutor> icoFoamExecutor;        
    const int resultsCount;
    const int syncTimeoutMax;
    std::unique_ptr<QThread> icoFoamThread;
    std::unique_ptr<QTimer> timer;
    std::unique_ptr<QElapsedTimer> elapsedTime;
    std::unique_ptr<std::map<int, bool>> syncResults;
};

}
#endif // ICOFOAMMANAGER_H
