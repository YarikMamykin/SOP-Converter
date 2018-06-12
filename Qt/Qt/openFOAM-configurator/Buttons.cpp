#include "Buttons.h"
#include <QRect>
#include "Logger.h"

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
    logging::Logger::getInstance()->log(QString("Button pressed"));
}
