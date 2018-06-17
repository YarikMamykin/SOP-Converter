#ifndef MENU_H
#define MENU_H

#include <QObject>
#include <QString>
#include <QMenuBar>
#include <QMenu>
#include <QAction>
#include "../../logging/Logger/Logger.h"
#include <map>
#include <memory>

namespace Ui
{

class Menu : public QMenuBar
{
public:
    explicit Menu(QWidget* parent = 0);
    virtual ~Menu();
public:
//    class MenuItem;
//    class MenuAction;

public slots:
    void showMessage();
private:
    std::map<QString, QMenu*> menuItem;
    std::map<QString, QAction*> menuAction;    
};

}
#endif // MENU_H
