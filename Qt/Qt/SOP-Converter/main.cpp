#include "MainWindow.h"
#include <QApplication>
#include "logging/Logger/Logger.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    logging::Logger::getInstance()->log(QString("Hello"), logging::LogDirection::file);
    return a.exec();
}
