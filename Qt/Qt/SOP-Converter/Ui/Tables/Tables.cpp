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
    for(int i = 0; i < 7; i++) this->insertRow(i);
    this->insertColumn(0);
    this->insertColumn(1);
    this->show();
}
