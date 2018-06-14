#include "Buttons.h"
#include "Logger.h"

/* StartConvertionButton */
/*
 *
*/
Ui::StartConvertionButton::StartConvertionButton(QString name, QWidget* parent) :
    QPushButton(name, parent)
{
    QObject::connect(this, SIGNAL(clicked()), SLOT(showMessage()));
}

Ui::StartConvertionButton::~StartConvertionButton()
{
    QObject::disconnect(this, 0, 0, 0);
}

void Ui::StartConvertionButton::showMessage()
{
    logging::Logger::getInstance()->log(this->text());
}

/* ResetSettingsButton */
/*
 *
*/
Ui::ResetSettingsButton::ResetSettingsButton(QString name, QWidget* parent) :
    QPushButton(name, parent)
{
    QObject::connect(this, SIGNAL(clicked()), SLOT(showMessage()));
}

Ui::ResetSettingsButton::~ResetSettingsButton()
{
    QObject::disconnect(this, 0, 0, 0);
}

void Ui::ResetSettingsButton::showMessage()
{
    logging::Logger::getInstance()->log(this->text());
}

/* SaveSettingsButton */
/*
 *
*/
Ui::SaveSettingsButton::SaveSettingsButton(QString name, QWidget* parent) :
    QPushButton(name, parent)
{
    QObject::connect(this, SIGNAL(clicked()), SLOT(showMessage()));
}

Ui::SaveSettingsButton::~SaveSettingsButton()
{
    QObject::disconnect(this, 0, 0, 0);
}

void Ui::SaveSettingsButton::showMessage()
{
    logging::Logger::getInstance()->log(this->text());
}
