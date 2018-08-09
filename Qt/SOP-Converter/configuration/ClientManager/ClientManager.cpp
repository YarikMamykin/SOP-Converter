#include "ClientManager.h"
#include "../../logging/Logger/Logger.h"
#include "../../logging/Messanger/Messanger.h"
#include "../../configuration/FileManager/FileManager.h"
#include "configuration/IcoFoamManager/IcoFoamManager.h"

using LogManager = logging::Logger;
using Messanger = logging::Messanger;
using FManager = configuration::FileManager;
using IcoFoam = configuration::IcoFoamManager;

configuration::ClientManager::ClientManager() :
    selectDialog(new QFileDialog)
{
    LogManager::getInstance()->log("ClientManager constructed");
    QObject::connect(configuration::Parser::getInstance(),
                     SIGNAL(notifyAll()),
                     this,
                     SIGNAL(notifyAll()), Qt::QueuedConnection);
    QObject::connect(configuration::Parser::getInstance(),
                     SIGNAL(startParsing()),
                     this,
                     SIGNAL(clearConsole()), Qt::QueuedConnection);
    QObject::connect(configuration::Parser::getInstance(),
                     SIGNAL(startSyncFiles()),
                     this,
                     SIGNAL(clearConsole()), Qt::QueuedConnection);
    QObject::connect(this,
                     SIGNAL(syncFiles()),
                     configuration::Parser::getInstance(),
                     SIGNAL(startSyncFiles()), Qt::QueuedConnection);
}

configuration::ClientManager::~ClientManager()
{
    QObject::disconnect(this,0,0,0);
    delete selectDialog;
    LogManager::getInstance()->log("ClientManager destructed");
}

void configuration::ClientManager::selectWorkspace()
{
    selectDialog->setFileMode(QFileDialog::DirectoryOnly);
    selectDialog->setNameFilter(QString("Select workspace directory"));
    selectDialog->setViewMode(QFileDialog::Detail);
    selectDialog->setOption(QFileDialog::ReadOnly);

    if(selectDialog->exec())
    {
        try
        {
            FManager::getInstance()->setPathToDir(FManager::getInstance()->getWorkDir(), selectDialog->selectedFiles()[0]);
        }
        catch(configuration::FileManager::Exception& e)
        {
            LogManager::getInstance()->log(e.what());
        }
    } else LogManager::getInstance()->log(QString("Workspace is not selected!"));
}

void configuration::ClientManager::selectMeshFile()
{
    selectDialog->setFileMode(QFileDialog::AnyFile);
    selectDialog->setNameFilter(tr("Mesh file *.unv"));
    selectDialog->setViewMode(QFileDialog::Detail);

    if(selectDialog->exec())
    {
        try
        {
            FManager::getInstance()->setPathToFile(FManager::getInstance()->getMeshFile(), selectDialog->selectedFiles()[0]);
        }
        catch(configuration::FileManager::Exception& e)
        {
            LogManager::getInstance()->log(e.what());
        }
    }else LogManager::getInstance()->log(QString("Mesh file is not selected!"));
}

void configuration::ClientManager::selectProjectFile()
{
    selectDialog->setFileMode(QFileDialog::AnyFile);
    selectDialog->setNameFilter(tr("Project file *.xml"));
    selectDialog->setViewMode(QFileDialog::Detail);

    if(selectDialog->exec())
    {
        try
        {
            FManager::getInstance()->setPathToFile(FManager::getInstance()->getProjectFile(), selectDialog->selectedFiles()[0]);
        }
        catch(configuration::FileManager::Exception& e)
        {
            LogManager::getInstance()->log(e.what());
        }
    }else LogManager::getInstance()->log(QString("Project file is not selected!"));
}

void configuration::ClientManager::startSyncMaps()
{
    if( FManager::getInstance()->getWorkDir().get()->path().isEmpty() ||
        FManager::getInstance()->getWorkDir().get()->path() == QString("."))
    {
        Messanger::getInstance()->showMessage("No workspace directory selected!");
        LogManager::getInstance()->log("No workspace directory selected!");
        emit enableUi();
        return;
    }
    else if(FManager::getInstance()->getMeshFile().get()->fileName().isEmpty())
    {
        Messanger::getInstance()->showMessage("No mesh file selected!");
        LogManager::getInstance()->log("No mesh file selected!");
        emit enableUi();
        return;
    }
    else emit syncMaps();
}

