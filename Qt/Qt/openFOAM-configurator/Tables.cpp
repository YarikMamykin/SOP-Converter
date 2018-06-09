#include "Tables.h"

Ui::SetTable::SetTable(QWidget* parent) :
    QTableWidget(parent)
{
    setDefaultProperties();
}

Ui::SetTable::~SetTable()
{
    this->hide();
}

void Ui::SetTable::setDefaultProperties()
{
    this->move(0, 0);
    for(int i = 0; i < 21; i++) this->insertRow(i);
    this->insertColumn(0);
    this->insertColumn(1);
    this->show();
}
