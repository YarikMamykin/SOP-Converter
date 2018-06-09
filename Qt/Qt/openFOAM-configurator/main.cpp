#include "mainwindow.h"
#include <QApplication>
#include <Messanger.h>
#include <QTimer>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    logging::Messanger::getInstance()->showMessage(QString("Hello"));
//    QTimer::singleShot(1000, &a, SLOT(quit()));
    return a.exec();
}
