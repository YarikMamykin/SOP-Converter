#include "ClientManager.h"
#include "../../logging/Logger/Logger.h"
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
    selectDialog->setFileMode(QFileDialog::Directory);
    selectDialog->setNameFilter(tr("Any (*)"));
    selectDialog->setViewMode(QFileDialog::Detail);

    QStringList selectionList;
    if(selectDialog->exec())
    {
        selectionList = selectDialog->selectedFiles();
    }
    LogManager::getInstance()->log(QString("Workspace selected -> ") + selectionList.join(" "));
}
