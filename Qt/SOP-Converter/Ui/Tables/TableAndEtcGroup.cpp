#include "TableAndEtcGroup.h"

Ui::TableAndEtcGroup::TableAndEtcGroup(std::shared_ptr<management::ClientManager> clientManager, QWidget *parent) :
    QWidget(parent),
    table(new Ui::SetTable(clientManager)),
    cdTable(new Ui::ControlDictTable(clientManager)),
    layout(new QHBoxLayout)
{
    layout->addWidget(table);
    layout->addWidget(cdTable);
    layout->setAlignment(Qt::AlignRight);
    layout->setStretch(0,1);
    this->setLayout(layout);

    QObject::connect(clientManager.get(),SIGNAL(clearTable()), table, SLOT(erase()), Qt::DirectConnection);
    QObject::connect(clientManager.get(),SIGNAL(clearTable()), cdTable, SLOT(erase()), Qt::DirectConnection);
}

Ui::TableAndEtcGroup::~TableAndEtcGroup()
{
    delete table;
    delete cdTable;
    delete layout;
}

