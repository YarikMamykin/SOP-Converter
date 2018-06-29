#include "Menu.h"

Ui::Menu::Menu(QWidget* parent) :
    QMenuBar(parent),    
    clientManager(std::make_shared<configuration::ClientManager>())
{
    items.push_back(new Menu::MenuItem());
    items[0]->setMenuItem(this->addMenu("&Open"));
    items[0]->addAction(new QAction("&Workspace",this));
    QObject::connect(items[0]->getActions()[0], &QAction::triggered, this, &Ui::Menu::openWorkspace);
    items[0]->addAction(new QAction("&Mesh file",this));
    QObject::connect(items[0]->getActions()[1], &QAction::triggered, this, &Ui::Menu::openMeshFile);
}

Ui::Menu::~Menu()
{
    for(auto e : items)
    {
        delete e;
    }
    items.clear();
}

void Ui::Menu::openWorkspace()
{
    logging::Logger::getInstance()->log(QString("Open -> Workspace"));
    clientManager.get()->selectWorkspace();
}

void Ui::Menu::openMeshFile()
{
    logging::Logger::getInstance()->log(QString("Open -> Mesh file"));
    clientManager.get()->selectMeshFile();
}

Ui::Menu::MenuItem::MenuItem()
{

}

Ui::Menu::MenuItem::~MenuItem()
{
    for(auto e : actions)
    {
        delete e;
    }
    actions.clear();
    delete menuItem;
}

void Ui::Menu::MenuItem::addAction(QAction *action)
{
    menuItem->addAction(action);
    actions.push_back(action);
}

std::vector<QAction*>& Ui::Menu::MenuItem::getActions()
{
    return actions;
}

void Ui::Menu::MenuItem::setMenuItem(QMenu* _menuItem)
{
    menuItem = _menuItem;
}


