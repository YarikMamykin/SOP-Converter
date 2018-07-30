#include "MainWindow.h"
#include <QDebug>
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QWidget(parent),
    clientManager(std::make_shared<configuration::ClientManager>()),
    ui(new Ui::MainWindow),
    menuBar(new Ui::Menu(clientManager, this)),
    tableAndEtc(new Ui::TableAndEtcGroup(clientManager, this)),
    tpField(new Ui::TransportPropertiesField(clientManager, this)),
    consoleAndButtons(new Ui::ConsoleAndButtonsGroup(clientManager, this)),
    layout(new QVBoxLayout)
{
    ui->setupUi(this);
    this->layout->addWidget(menuBar);
    this->layout->addWidget(tableAndEtc);
    this->layout->addWidget(tpField);
    this->layout->addWidget(consoleAndButtons);
    this->setLayout(this->layout);    
    this->setWindowTitle("SOP-Converter");
    this->setMinimumSize(1000, 400);
    QObject::connect(clientManager.get(),
                     SIGNAL(syncMaps()),
                     this,
                     SLOT(syncMaps()), Qt::QueuedConnection);
    logging::Logger::getInstance()->log("Window constructed");
}

MainWindow::~MainWindow()
{
    QObject::disconnect(this,0,0,0);
    delete menuBar;           logging::Logger::getInstance()->log("menuBar deinited", logging::LogDirection::file);
    delete tableAndEtc;       logging::Logger::getInstance()->log("tableAndEtc deinited", logging::LogDirection::file);
    delete tpField;           logging::Logger::getInstance()->log("TransportPropertiesField deinited", logging::LogDirection::file);
    delete consoleAndButtons; logging::Logger::getInstance()->log("ConsoleAndButtons deinited", logging::LogDirection::file);
    delete layout;            logging::Logger::getInstance()->log("Window layout deinited", logging::LogDirection::file);
    delete ui;                logging::Logger::getInstance()->log("ui deinited", logging::LogDirection::file);
    logging::Logger::getInstance()->log("Window destroyed", logging::LogDirection::file);
}

void MainWindow::syncMaps()
{

}
