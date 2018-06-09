#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtWidgets>
#include <QHBoxLayout>
#include "Buttons.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QWidget // make window as widget!!
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:        
    QHBoxLayout* padLayout;
    Ui::OkButton* okbutton;

};

#endif // MAINWINDOW_H
