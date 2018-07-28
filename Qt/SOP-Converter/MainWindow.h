#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include "logging/Logger/Logger.h"
#include "Ui/Console/ConsoleAndButtonsGroup.h"
#include "Ui/Menu/Menu.h"
#include "Ui/Tables/TableAndEtcGroup.h"
#include "configuration/ClientManager/ClientManager.h"
#include <memory>

namespace Ui {
class MainWindow;
}

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    virtual ~MainWindow();

private:
    std::shared_ptr<configuration::ClientManager> clientManager;
    Ui::MainWindow *ui;
    Ui::Menu* menuBar;
    Ui::TableAndEtcGroup* tableAndEtc;
    Ui::ConsoleAndButtonsGroup* consoleAndButtons;
    QVBoxLayout* layout;
};

#endif // MAINWINDOW_H
