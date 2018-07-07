#include "MainWindow.h"
#include <QApplication>
#include <QFileDialog>
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
                     SLOT(logToFile(const QString&)));

    QObject::connect(configuration::FileManager::getInstance(),
                     SIGNAL(parseFiles()),
                     configuration::Parser::getInstance(),
                     SLOT(startParsing()));


    logging::Logger::getInstance()->log(QString("App start"), logging::LogDirection::file);
    MainWindow w;
    w.show();

    configuration::ProjectFile pf;
    pf.setFileStructure();
    configuration::FileManager::getInstance()->saveProjectFile(pf);
//    QFileDialog::getOpenFileName(0,QString("Open Image"), "./", QString("Image Files (*.png *.jpg *.bmp)"));
//    QFileDialog::getOpenFileName(0,QString("Open Image"), "./", QString("All Files (*)"));
    return a.exec();
}
