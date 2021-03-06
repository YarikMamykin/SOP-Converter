#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include "logging/Logger/Logger.h"
#include "Ui/Console/ConsoleAndButtonsGroup.h"
#include "Ui/Menu/Menu.h"
#include "Ui/Tables/TableAndEtcGroup.h"
#include "management/ClientManager/ClientManager.h"
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

    std::shared_ptr<management::ClientManager> getClientManager();
private:
    std::shared_ptr<management::ClientManager> clientManager;
    Ui::MainWindow *ui;
    Ui::Menu* menuBar;
    Ui::TableAndEtcGroup* tableAndEtc;
    Ui::TransportPropertiesField* tpField;
    Ui::ConsoleAndButtonsGroup* consoleAndButtons;
    QVBoxLayout* layout;
};

#endif // MAINWINDOW_H
