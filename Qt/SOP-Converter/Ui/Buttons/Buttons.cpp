#include "Buttons.h"


Ui::Button::Button(std::shared_ptr<configuration::ClientManager> cm, QString name, QWidget* parent) :
    QPushButton(name, parent),
    pal(new QPalette),
    clientManager(cm)
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

void Ui::Button::disable()
{
    this->setDisabled(true);
}

//void Ui::Button::setColor(Qt::GlobalColor color, Qt::GlobalColor fontColor)
//{

//}


