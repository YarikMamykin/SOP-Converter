#include "Buttons.h"


Ui::Button::Button() : QPushButton(QString("Unnamed")), pal() {}

Ui::Button::Button(QString name, QWidget* parent) :
    QPushButton(name, parent),
    pal(new QPalette)
{
    QObject::connect(this, SIGNAL(clicked()), SLOT(showMessage()));
    this->setFixedSize(200, 50);
}

Ui::Button::~Button()
{
    QObject::disconnect(this, 0, 0, 0);
    delete pal;
}

void Ui::Button::showMessage()
{
    logging::Logger::getInstance()->log(this->text());
}

//void Ui::Button::setColor(Qt::GlobalColor color, Qt::GlobalColor fontColor)
//{

//}


