#include "ConsoleAndButtonsGroup.h"

Ui::ConsoleAndButtonsGroup::ConsoleAndButtonsGroup(QWidget *parent) :
    QWidget(parent),
    buttons(new Ui::ButtonsGroup),
    console(new Ui::Console),
    layout(new QHBoxLayout)
{
    layout->addWidget(console);
    layout->addWidget(buttons);
    this->setLayout(layout);
}

Ui::ConsoleAndButtonsGroup::~ConsoleAndButtonsGroup()
{
    delete buttons;
    delete console;
    delete layout;
}
