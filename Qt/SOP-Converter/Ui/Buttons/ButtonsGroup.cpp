#include "ButtonsGroup.h"

Ui::ButtonsGroup::ButtonsGroup(std::shared_ptr<configuration::ClientManager> clientManager, QWidget* parent) :
    QWidget(parent),
    startConvertion(new Ui::Button(clientManager, "Start conversion")),
    resetSettings(new Ui::Button(clientManager, "Reset settings")),
    saveSettings(new Ui::Button(clientManager, "Save settings")),
    clearConsole(new Ui::Button(clientManager, "Clear CONSOLE")),
    layout(new QVBoxLayout)
{
    layout->addWidget(startConvertion);
    layout->addWidget(resetSettings);
    layout->addWidget(saveSettings);
    layout->addWidget(clearConsole);
    this->setLayout(layout);
}

Ui::Button* Ui::ButtonsGroup::ButtonsGroup::getStartConversionButton() {return startConvertion;}
Ui::Button* Ui::ButtonsGroup::ButtonsGroup::getResetSettingsButton()   {return resetSettings;}
Ui::Button* Ui::ButtonsGroup::ButtonsGroup::getSaveSettingsButton()    {return saveSettings;}
Ui::Button* Ui::ButtonsGroup::ButtonsGroup::getClearConsoleButton()    {return clearConsole;}

Ui::ButtonsGroup::~ButtonsGroup()
{
    delete startConvertion;
    delete resetSettings;
    delete saveSettings;
    delete clearConsole;
    delete layout;
}
