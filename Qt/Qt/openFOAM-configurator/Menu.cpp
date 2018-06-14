#include "Menu.h"

Ui::Menu::Menu() :
    QMenuBar(),
    menuItem(),
    menuAction()
{
    menuItem.insert(std::make_pair(QString("Open"), this->addMenu("&Open")));
    menuAction.insert(std::make_pair(QString("Open"), new QAction("&Workspace",this)));
    menuItem.find(QString("Open"))->second->addAction(menuAction.find(QString("Open"))->second);

    QObject::connect(menuAction.find(QString("Open"))->second, &QAction::triggered, this, &Ui::Menu::showMessage);
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
        menuItem.erase(menuItem.begin());
    }
}

void Ui::Menu::showMessage()
{
    logging::Logger::getInstance()->log(QString("Action triggered"), logging::LogDirection::console);
}
