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

private:    
    void notifyUi();
    void notifyBe();
private:
    QFileDialog* selectDialog;
};

}

#endif // CLIENTMANAGER_H
