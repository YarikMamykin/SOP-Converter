#include "MainWindow.h"
#include <QApplication>
#include "logging/Logger/Logger.h"
#include "configuration/FileManager/FileManager.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);    
    QObject::connect(logging::Logger::getInstance(), SIGNAL(logToFile(const QString&)), configuration::FileManager::getInstance(), SLOT(logToFile(const QString&)));
    logging::Logger::getInstance()->log(QString("App start"), logging::LogDirection::file);
    MainWindow w;
    w.show();    
    return a.exec();
}
