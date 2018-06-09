#include "mainwindow.h"
#include <QApplication>
#include "Messanger.h"
#include "Logger.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
