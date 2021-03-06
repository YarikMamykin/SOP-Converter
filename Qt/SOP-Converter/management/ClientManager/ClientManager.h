#ifndef CLIENTMANAGER_H
#define CLIENTMANAGER_H

#include <QObject>
#include <QFileDialog>

namespace management
{

class ClientManager final : public QObject
{
    Q_OBJECT
public:
    explicit ClientManager();
    virtual ~ClientManager();

    void selectWorkspace();
    void selectMeshFile();
    void selectProjectFile();
signals:
    void clearConsole();
    void clearTable();
    void clearTpSets();
    void notifyAll();
    void syncFiles();    
    void syncMaps();
    void disableUi();
    void enableUi();
    void stopCalculation();
public slots:
    void startSyncMaps();
private:
    QFileDialog* selectDialog;
};

}

#endif // CLIENTMANAGER_H
