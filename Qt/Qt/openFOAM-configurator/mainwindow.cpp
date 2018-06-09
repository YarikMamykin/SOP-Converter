#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QWidget(parent),
    /* Layouts */
    mainLayout(new QVBoxLayout), buttonsLayout(new QVBoxLayout),
    buttonsAndConsoleLayout(new QHBoxLayout), tableAndOthersLayout(new QHBoxLayout),
    /* Main widgets groups */
    buttonsGroup(new QWidget), buttonsAndConsoleGroup(new QWidget), tableAndOthersGroup(new QWidget),
    /* Control elements */
    okbutton(new Ui::OkButton),
    table(new Ui::SetTable),
    console(new Ui::Console)
{
    tableAndOthersLayout->addWidget(table);
    buttonsAndConsoleLayout->addWidget(console);
    buttonsAndConsoleLayout->addWidget(okbutton);
    mainLayout->addWidget(tableAndOthersGroup);
    mainLayout->addWidget(buttonsAndConsoleGroup);
    tableAndOthersGroup->setLayout(tableAndOthersLayout);
    buttonsAndConsoleGroup->setLayout(buttonsAndConsoleLayout);
    this->setLayout(mainLayout);
    logging::Logger::getInstance()->sendLogToConsole("window inited");
}

MainWindow::~MainWindow()
{    
    delete console;
    delete table;
    delete okbutton;
    delete tableAndOthersGroup;  delete buttonsAndConsoleGroup; delete buttonsGroup;
    delete tableAndOthersLayout;
    delete buttonsAndConsoleLayout;
    delete buttonsLayout; delete mainLayout;
}
