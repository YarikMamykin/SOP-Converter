#include "MainWindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainWindow),
    menuBar(new Ui::Menu(this)),
    tableAndEtc(new Ui::TableAndEtcGroup(this)),
    consoleAndButtons(new Ui::ConsoleAndButtonsGroup(this)),
    layout(new QVBoxLayout)
{
    ui->setupUi(this);
    this->layout->addWidget(menuBar);
    this->layout->addWidget(tableAndEtc);
    this->layout->addWidget(consoleAndButtons);
    this->setLayout(this->layout);    
    this->setWindowTitle("SOP-Converter");
    this->setMinimumSize(1000, 400);
    logging::Logger::getInstance()->log("Window inited");
}

MainWindow::~MainWindow()
{
    delete menuBar;           logging::Logger::getInstance()->log("menuBar deinited", logging::LogDirection::file);
    delete tableAndEtc;       logging::Logger::getInstance()->log("tableAndEtc deinited", logging::LogDirection::file);
    delete consoleAndButtons; logging::Logger::getInstance()->log("ConsoleAndButtons deinited", logging::LogDirection::file);
    delete layout;            logging::Logger::getInstance()->log("Window layout deinited", logging::LogDirection::file);
    delete ui;                logging::Logger::getInstance()->log("ui deinited", logging::LogDirection::file);
    logging::Logger::getInstance()->log("Window deinited", logging::LogDirection::file);
}
