#include "MainWindow.h"
#include <QApplication>
#include <QFileDialog>
#include <QDir>
#include <QThread>
#include <QDebug>
#include "general/general.h"
#include "logging/Logger/Logger.h"
#include "logging/Messanger/Messanger.h"
#include "management/FileManager/FileManager.h"
#include "configuration/ProjectFile/ProjectFile.h"
#include "configuration/Parser/Parser.h"
#include "filetypes/FoamFiles.h"
#include <iostream>

int main(int argc, char *argv[])
{
//    QApplication a(argc, argv);
//    logging::Logger::getInstance()->log(QString("App start"), logging::LogDirection::file);
//    MainWindow w;
//    w.show();

//    filetypes::FileBoundary f("/home/yarik/Documents/diploma/lab2/constant/polyMesh/boundary");
//    filetypes::FileU f("/home/yarik/Documents/diploma/lab2/0/U");
//    filetypes::FileControlDict f("/home/yarik/Documents/diploma/lab2/system/controlDict");
    filetypes::FileTransportProperties f("/home/yarik/Documents/diploma/lab2/constant/transportProperties");
    std::cout << static_cast<int>(f.parse()) << std::endl;
    std::cout << "Data size = " << f.getData().get()->size() << std::endl;
    for(auto& e : *f.getData().get())
    {
        std::cout << e.first << ":" << std::endl;
        for(auto& ee : e.second)
        {
            std::cout << ee.first << " " << ee.second << std::endl;
        }
    }
    std::cout << static_cast<int>(f.save()) << std::endl;
//    configuration::ProjectFile pf;
//    pf.setFileStructure();
//    configuration::FileManager::getInstance()->saveProjectFile(pf);

//    int retcode = a.exec();
//    logging::Logger::getInstance()->log(QString("App END. Retcode = %1").arg(retcode));
//    return retcode;
    return 0;
}
