#ifndef CLIENTMANAGER_H
#define CLIENTMANAGER_H

#include <QObject>
#include <QFileDialog>

namespace configuration
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
public slots:
    void startSyncMaps();
    void collectSyncResults(int, bool);
private:
    QFileDialog* selectDialog;
};

}

#endif // CLIENTMANAGER_H
