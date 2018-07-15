#include "MainWindow.h"
#include <QApplication>
#include <QFileDialog>
#include <QDir>
#include "general/general.h"
#include "logging/Logger/Logger.h"
#include "logging/Messanger/Messanger.h"
#include "configuration/FileManager/FileManager.h"
#include "configuration/ProjectFile/ProjectFile.h"
#include "configuration/Parser/Parser.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);            
    QObject::connect(logging::Logger::getInstance(),
                     SIGNAL(logToFile(const QString&)),
                     configuration::FileManager::getInstance(),
                     SLOT(logToFile(const QString&)), Qt::QueuedConnection);

    logging::Logger::getInstance()->log(QString("App start"), logging::LogDirection::file);
    MainWindow w;
    w.show();

//    configuration::ProjectFile pf;
//    pf.setFileStructure();
//    configuration::FileManager::getInstance()->saveProjectFile(pf);

    return a.exec();
}
