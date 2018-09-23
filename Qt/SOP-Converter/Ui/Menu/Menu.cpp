#include "Menu.h"
#include "../../management/FileManager/FileManager.h"
using FileManager = management::FileManager;

/* ---------------------------------------------------------------------- */
/* -- Menu -- */
/* ---------------------------------------------------------------------- */

Ui::Menu::Menu(std::shared_ptr<management::ClientManager> cm, QWidget* parent) :
    QMenuBar(parent),    
    clientManager(cm)
{
    QObject::connect(clientManager.get(),
                     &management::ClientManager::disableUi,
                     this,
                     &Ui::Menu::disable, Qt::QueuedConnection);
    QObject::connect(clientManager.get(),
                     &management::ClientManager::enableUi,
                     this,
                     &Ui::Menu::enable, Qt::QueuedConnection);
    items.push_back(new Menu::MenuItem());
    items[0]->setMenuItem(this->addMenu("&Open"));
    items[0]->addAction(new QAction("&Workspace",this));
    QObject::connect(items[0]->getActions()[0], &QAction::triggered, this, &Ui::Menu::openWorkspace);
    items[0]->addAction(new QAction("&Mesh file",this));
    QObject::connect(items[0]->getActions()[1], &QAction::triggered, this, &Ui::Menu::openMeshFile);
    items[0]->addAction(new QAction("&Project file",this));
    QObject::connect(items[0]->getActions()[2], &QAction::triggered, this, &Ui::Menu::openProjectFile);

    items.push_back(new Menu::MenuItem());
    items[1]->setMenuItem(this->addMenu("&Reload"));
    items[1]->addAction(new QAction("&Workspace",this));
    QObject::connect(items[1]->getActions()[0], &QAction::triggered, this, &Ui::Menu::reloadWorkspace);
}

Ui::Menu::~Menu()
{
    QObject::disconnect(this,0,0,0);
    logging::Logger::getInstance()->log("Attempting to delete menu");
    for(auto e : items)
    {
        delete e;
    }
    items.clear();
    logging::Logger::getInstance()->log("Menu deleted!");
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

void Ui::Menu::openProjectFile()
{
    logging::Logger::getInstance()->log(QString("Open -> Project file"));
    clientManager.get()->selectProjectFile();
}

void Ui::Menu::reloadWorkspace()
{
    using ValidPoint = management::FileManager::ValidatePathsPoint;
    FileManager::getInstance()->validatePaths(ValidPoint::workDir);
}

void Ui::Menu::disable()
{
    this->setDisabled(true);
}

void Ui::Menu::enable()
{
    this->setDisabled(false);
}

/* ---------------------------------------------------------------------- */
/* -- MenuItem -- */
/* ---------------------------------------------------------------------- */

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


