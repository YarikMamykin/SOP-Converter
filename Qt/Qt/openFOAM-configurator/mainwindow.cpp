#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    buttonsPad(new QWidget(this)),
    padLayout(new QHBoxLayout),
    okbutton(new Ui::OkButton)
{
    ui->setupUi(this);    
    padLayout->setMargin(100);
    padLayout->setSpacing(200);
//    okbutton->setDisabled(false);
    padLayout->addWidget(okbutton);
//    buttonsPad->setLayout(padLayout);
    this->setLayout(padLayout);
    okbutton->show();
//    buttonsPad->resize(320, 440);

//    buttonsPad->show();


}

MainWindow::~MainWindow()
{
    delete okbutton;
    delete padLayout;
    delete buttonsPad;
    delete ui;
}
