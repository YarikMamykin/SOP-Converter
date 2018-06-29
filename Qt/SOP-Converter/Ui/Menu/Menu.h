#ifndef MENU_H
#define MENU_H

#include <QObject>
#include <QString>
#include <QMenuBar>
#include <QMenu>
#include <QAction>
#include "../../logging/Logger/Logger.h"
#include "../../configuration/ClientManager/ClientManager.h"
#include <vector>
#include <memory>

namespace Ui
{

class Menu : public QMenuBar
{    
public:
    explicit Menu(QWidget* parent = 0);
    virtual ~Menu();
public:
    class MenuItem;
//    class MenuAction;

public slots:
    void openWorkspace();
    void openMeshFile();
private:
    std::vector<Menu::MenuItem*> items;
    std::shared_ptr<configuration::ClientManager> clientManager;
};

class Menu::MenuItem : public QObject
{    
public:
    explicit MenuItem();
    virtual ~MenuItem();

    void addAction(QAction* action);
    std::vector<QAction*>& getActions();
    void setMenuItem(QMenu* _menuItem);
private:
    std::vector<QAction*> actions;
    QMenu* menuItem;
};

}
#endif // MENU_H
