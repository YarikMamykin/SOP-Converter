#ifndef CLIENTMANAGER_H
#define CLIENTMANAGER_H

#include <QObject>
#include <QFileDialog>

namespace configuration
{

class ClientManager : public QObject
{
    Q_OBJECT
public:
    explicit ClientManager();
    virtual ~ClientManager();

    void selectWorkspace();
private:
    QFileDialog* selectDialog;
};

}

#endif // CLIENTMANAGER_H
