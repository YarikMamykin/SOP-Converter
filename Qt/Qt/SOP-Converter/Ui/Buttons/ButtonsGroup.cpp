#include "ButtonsGroup.h"

Ui::ButtonsGroup::ButtonsGroup(QWidget* parent) :
    QWidget(parent),
    startConvertion(new Ui::Button("Start conversion")),
    resetSettings(new Ui::Button("Reset settings")),
    saveSettings(new Ui::Button("Save settings")),
    layout(new QVBoxLayout)
{
    layout->addWidget(startConvertion);
    layout->addWidget(resetSettings);
    layout->addWidget(saveSettings);
    this->setLayout(layout);
}

Ui::ButtonsGroup::~ButtonsGroup()
{
    delete startConvertion;
    delete resetSettings;
    delete saveSettings;
    delete layout;
}
