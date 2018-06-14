#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QWidget(parent),
    /* Layouts */
    mainLayout(new QVBoxLayout),
    buttonsLayout(new QVBoxLayout),
    buttonsAndConsoleLayout(new QHBoxLayout),
    tableAndOthersLayout(new QHBoxLayout),
    /* Main widgets groups */
    buttonsGroup(new QWidget),
    buttonsAndConsoleGroup(new QWidget),
    tableAndOthersGroup(new QWidget),
    /* Control elements */
    startConvertionButton(new Ui::StartConvertionButton),
    resetSettingsButton(new Ui::ResetSettingsButton),
    saveSettingsButton(new Ui::SaveSettingsButton),
    table(new Ui::SetTable),
    console(new Ui::Console),
    menu(new Ui::Menu)
{
    tableAndOthersLayout->addWidget(table.get());

    buttonsLayout->addWidget(startConvertionButton.get());
    buttonsLayout->addWidget(resetSettingsButton.get());
    buttonsLayout->addWidget(saveSettingsButton.get());
    buttonsGroup->setLayout(buttonsLayout.get());

    buttonsAndConsoleLayout->addWidget(console.get());
    buttonsAndConsoleLayout->addWidget(buttonsGroup.get());

    mainLayout->addWidget(menu.get());
    mainLayout->addWidget(tableAndOthersGroup.get());
    mainLayout->addWidget(buttonsAndConsoleGroup.get());

    tableAndOthersGroup->setLayout(tableAndOthersLayout.get());
    buttonsAndConsoleGroup->setLayout(buttonsAndConsoleLayout.get());
    this->setLayout(mainLayout.get());

    logging::Logger::getInstance()->log("Window created");
}

MainWindow::~MainWindow()
{    
    delete console.release();
    delete table.release();
    delete startConvertionButton.release();
    delete resetSettingsButton.release();
    delete saveSettingsButton.release();
    delete tableAndOthersGroup.release();
    delete buttonsAndConsoleGroup.release();
    delete buttonsGroup.release();
    delete tableAndOthersLayout.release();
    delete buttonsAndConsoleLayout.release();
    delete buttonsLayout.release();
    delete mainLayout.release();
}
