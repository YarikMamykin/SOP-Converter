#include "ConsoleAndButtonsGroup.h"

Ui::ConsoleAndButtonsGroup::ConsoleAndButtonsGroup(std::shared_ptr<configuration::ClientManager> clientManager, QWidget *parent) :
    QWidget(parent),
    buttons(new Ui::ButtonsGroup(clientManager)),
    console(new Ui::Console(clientManager)),
    layout(new QHBoxLayout)
{
    layout->addWidget(console);
    layout->addWidget(buttons);
    this->setLayout(layout);

    QObject::connect(buttons->getClearConsoleButton(), SIGNAL(clicked()), console, SLOT(clear()));
}

Ui::ConsoleAndButtonsGroup::~ConsoleAndButtonsGroup()
{
    QObject::disconnect(buttons->getClearConsoleButton(), SIGNAL(clicked()), console, SLOT(clear()));
    delete buttons;
    delete console;
    delete layout;
}
