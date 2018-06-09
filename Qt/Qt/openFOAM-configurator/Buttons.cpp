#include "Buttons.h"
#include <QRect>

Ui::OkButton::OkButton(QString name, QWidget* parent) :
    QPushButton(name, parent)
{
    QObject::connect(this, SIGNAL(clicked()), SLOT(showMessage()));
}

Ui::OkButton::~OkButton()
{
    QObject::disconnect(this, 0, 0, 0);
}

void Ui::OkButton::showMessage()
{
    QRect r = this->rect();
    logging::Messanger::getInstance()->showMessage(QString().sprintf("%d-%d-%d-%d",r.left(),r.top(),r.right(),r.bottom()));
}
