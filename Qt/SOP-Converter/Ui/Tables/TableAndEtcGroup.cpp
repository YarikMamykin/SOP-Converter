#include "TableAndEtcGroup.h"

Ui::TableAndEtcGroup::TableAndEtcGroup(std::shared_ptr<configuration::ClientManager> clientManager, QWidget *parent) :
    QWidget(parent),
    table(new Ui::SetTable(clientManager)),
    tpField(new Ui::TransportPropertiesField(clientManager)),
    layout(new QHBoxLayout)
{
    layout->addWidget(table);
    layout->addLayout(tpField);
    layout->setAlignment(Qt::AlignLeft);
    this->setLayout(layout);

    QObject::connect(clientManager.get(),SIGNAL(clearTable()), table, SLOT(erase()), Qt::DirectConnection);
}

Ui::TableAndEtcGroup::~TableAndEtcGroup()
{
    delete table;
    delete layout;
}

