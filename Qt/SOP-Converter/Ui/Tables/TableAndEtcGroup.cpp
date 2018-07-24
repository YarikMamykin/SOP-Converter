#include "TableAndEtcGroup.h"

Ui::TableAndEtcGroup::TableAndEtcGroup(QWidget *parent) :
    QWidget(parent),
    table(new Ui::SetTable),
    layout(new QHBoxLayout)
{
    layout->addWidget(table);
    layout->setAlignment(Qt::AlignLeft);
    this->setLayout(layout);
}

Ui::TableAndEtcGroup::~TableAndEtcGroup()
{
    delete table;
    delete layout;
}

