#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtWidgets>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <memory>
#include "Buttons.h"
#include "Tables.h"
#include "Console.h"
#include "Logger.h"

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
/* Layouts */
    QVBoxLayout* mainLayout;
    QVBoxLayout* buttonsLayout;
    QHBoxLayout* buttonsAndConsoleLayout;
    QHBoxLayout* tableAndOthersLayout;
/* Main widgets groups */
    QWidget* buttonsGroup;
    QWidget* buttonsAndConsoleGroup;
    QWidget* tableAndOthersGroup;
/* Control elements */
    Ui::OkButton* okbutton;
    Ui::SetTable* table;
    Ui::Console* console;
};

#endif // MAINWINDOW_H
