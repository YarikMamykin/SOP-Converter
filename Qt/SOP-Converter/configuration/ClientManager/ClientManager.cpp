#include "ClientManager.h"
#include "../../logging/Logger/Logger.h"
#include "../../configuration/FileManager/FileManager.h"

using LogManager = logging::Logger;
using FManager = configuration::FileManager;

configuration::ClientManager::ClientManager() :
    selectDialog(new QFileDialog)
{
    LogManager::getInstance()->log("ClientManager constructed");
}

configuration::ClientManager::~ClientManager()
{
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
