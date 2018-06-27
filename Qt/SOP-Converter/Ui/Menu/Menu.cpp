#include "Menu.h"

Ui::Menu::Menu(QWidget* parent) :
    QMenuBar(parent),
    menuItem(),
    menuAction(),
    clientManager(std::make_shared<configuration::ClientManager>())
{
    menuItem.insert(std::make_pair(QString("Open"), this->addMenu("&Open")));
    menuAction.insert(std::make_pair(QString("Open"), new QAction("&Workspace",this)));
    menuItem.find(QString("Open"))->second->addAction(menuAction.find(QString("Open"))->second);

    QObject::connect(menuAction.find(QString("Open"))->second, &QAction::triggered, this, &Ui::Menu::openWorkspace);
}

Ui::Menu::~Menu()
{
    for(auto e : menuItem)
    {
        delete e.second;
        menuItem.erase(menuItem.begin());
    }

    for(auto e : menuAction)
    {
        delete e.second;
        menuAction.erase(menuAction.begin());
    }
}

void Ui::Menu::openWorkspace()
{
    logging::Logger::getInstance()->log(QString("Open -> Workspace"));
    clientManager.get()->selectWorkspace();
}
