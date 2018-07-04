#include "ButtonsGroup.h"

Ui::ButtonsGroup::ButtonsGroup(QWidget* parent) :
    QWidget(parent),
    startConvertion(new Ui::Button("Start conversion")),
    resetSettings(new Ui::Button("Reset settings")),
    saveSettings(new Ui::Button("Save settings")),
    clearConsole(new Ui::Button("Clear CONSOLE")),
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
