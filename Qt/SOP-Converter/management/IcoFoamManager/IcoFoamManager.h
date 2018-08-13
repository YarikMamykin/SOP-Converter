#ifndef ICOFOAMMANAGER_H
#define ICOFOAMMANAGER_H

#include <QObject>
#include <QThread>
#include <QProcess>
#include <QTimer>
#include <QElapsedTimer>
#include <QStringList>
#include <QTextStream>
#include <memory>
#include "../../configuration/Parser/Parser.h"
#include "../../logging/Logger/Logger.h"

namespace management
{

class IcoFoamOutputProcessor : public QObject
{
    Q_OBJECT
public:
    explicit IcoFoamOutputProcessor();
    virtual ~IcoFoamOutputProcessor();
    void operator ()();
signals:
    void finished();
public slots:
    void observe();
private:
    const int readLineTimeout;
};

class IcoFoamManager final : public QObject
{
    Q_OBJECT
private:
    explicit IcoFoamManager();
    explicit IcoFoamManager(const IcoFoamManager&) = delete;
    virtual ~IcoFoamManager();

    friend class IcoFoamOutputProcessor;
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
    void doProcessStandartOut();
private slots:
    void handleSyncFail();

private:
    // clientManager cannot be a member of static class!!! --> causes core dump
    const int resultsCount;
    const int syncTimeoutMax;
    const int waitForReadyReadTimeout;

    std::unique_ptr<QTimer> timer;
    std::unique_ptr<QElapsedTimer> elapsedTime;
    std::unique_ptr<std::map<int, bool>> syncResults;
};



}
#endif // ICOFOAMMANAGER_H
