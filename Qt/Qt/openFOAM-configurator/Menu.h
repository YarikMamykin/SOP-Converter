#ifndef MENU_H
#define MENU_H

#include <QObject>
#include <QString>
#include <QMenuBar>
#include <QMenu>
#include <QAction>
#include <Logger.h>
#include <map>
#include <memory>

namespace Ui
{

class Menu : public QMenuBar
{
public:
    explicit Menu();
    virtual ~Menu();


private:
    std::map<QString, QMenu*> menuItem;
    std::map<QString, QAction*> menuAction;
public slots:
    void showMessage();
};

}
#endif // MENU_H
