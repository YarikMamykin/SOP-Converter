#include "ConsoleAndButtonsGroup.h"

Ui::ConsoleAndButtonsGroup::ConsoleAndButtonsGroup(std::shared_ptr<management::ClientManager> clientManager, QWidget *parent) :
    QWidget(parent),
    buttons(new Ui::ButtonsGroup(clientManager)),
    console(new Ui::Console(clientManager)),
    layout(new QHBoxLayout)
{
    layout->addWidget(console);
    layout->addWidget(buttons);
    this->setLayout(layout);
}

Ui::ConsoleAndButtonsGroup::~ConsoleAndButtonsGroup()
{
    QObject::disconnect(this,0,0,0);
    delete buttons;
    delete console;
    delete layout;
}
