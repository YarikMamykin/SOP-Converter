#include "ClientManager.h"
#include "../../logging/Logger/Logger.h"
#include "../../configuration/FileManager/FileManager.h"

using LogManager = logging::Logger;

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
            configuration::FileManager::getInstance()->setWorkDirPath(selectDialog->selectedFiles()[0]);
        }
        catch(configuration::FileManager::Exception& e)
        {
            LogManager::getInstance()->log(e.what());
        }
    }
}

void configuration::ClientManager::selectMeshFile()
{
    selectDialog->setFileMode(QFileDialog::AnyFile);
    selectDialog->setNameFilter(tr("Mesh file (*.unv)"));
    selectDialog->setViewMode(QFileDialog::Detail);

    if(selectDialog->exec())
    {
        try
        {
            configuration::FileManager::getInstance()->setMeshFilePath(selectDialog->selectedFiles()[0]);
        }
        catch(configuration::FileManager::Exception& e)
        {
            LogManager::getInstance()->log(e.what());
        }
    }
}
