#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtWidgets>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include "Buttons.h"
#include "Tables.h"
#include "Console.h"

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
    QVBoxLayout* mainLayout;
    QVBoxLayout* buttonsLayout;
    QHBoxLayout* buttonsAndConsoleLayout;
    QHBoxLayout* tableAndOthersLayout;
    QWidget* buttonsGroup;
    QWidget* buttonsAndConsoleGroup;
    QWidget* tableAndOthersGroup;


    Ui::OkButton* okbutton;
    Ui::SetTable* table;
    Ui::Console* console;
};

#endif // MAINWINDOW_H
