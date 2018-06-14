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
#include "Menu.h"

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
    std::unique_ptr<QVBoxLayout> mainLayout;
    std::unique_ptr<QVBoxLayout> buttonsLayout;
    std::unique_ptr<QHBoxLayout> buttonsAndConsoleLayout;
    std::unique_ptr<QHBoxLayout> tableAndOthersLayout;
/* Main widgets groups */
    std::unique_ptr<QWidget> buttonsGroup;
    std::unique_ptr<QWidget> buttonsAndConsoleGroup;
    std::unique_ptr<QWidget> tableAndOthersGroup;
/* Control elements */
    std::unique_ptr<Ui::StartConvertionButton> startConvertionButton;
    std::unique_ptr<Ui::ResetSettingsButton>   resetSettingsButton;
    std::unique_ptr<Ui::SaveSettingsButton>    saveSettingsButton;
    std::unique_ptr<Ui::SetTable> table;
    std::unique_ptr<Ui::Console>  console;
    std::unique_ptr<Ui::Menu>     menu;
};

#endif // MAINWINDOW_H
