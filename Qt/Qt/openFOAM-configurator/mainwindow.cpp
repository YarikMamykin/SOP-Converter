#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QWidget(parent),
    padLayout(new QHBoxLayout),
    okbutton(new Ui::OkButton)
{
    padLayout->setMargin(100);
    padLayout->setSpacing(200);
    padLayout->addWidget(okbutton);
    this->setLayout(padLayout);
//    okbutton->show();
}

MainWindow::~MainWindow()
{
    delete okbutton;
    delete padLayout;
}
