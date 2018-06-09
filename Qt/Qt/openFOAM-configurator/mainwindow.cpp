#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QWidget(parent),
    mainLayout(new QVBoxLayout),
    buttonsLayout(new QHBoxLayout),
    okbutton(new Ui::OkButton),
    table(new Ui::SetTable)
{
    buttonsLayout->setMargin(0);
    buttonsLayout->setSpacing(11);
    buttonsLayout->addWidget(table, 0, Qt::AlignLeft);
    buttonsLayout->addWidget(okbutton, 0, Qt::AlignRight | Qt::AlignAbsolute);
    this->setLayout(buttonsLayout);
    okbutton->move(200,200);
}

MainWindow::~MainWindow()
{
    delete okbutton;
    delete table;
}
