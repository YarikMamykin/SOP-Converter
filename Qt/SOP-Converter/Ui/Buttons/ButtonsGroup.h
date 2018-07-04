#ifndef BUTTONSGROUP_H
#define BUTTONSGROUP_H

#include <QWidget>
#include <QVBoxLayout>
#include "Buttons.h"

namespace Ui
{

class ButtonsGroup : public QWidget
{
public:
    explicit ButtonsGroup(QWidget* parent = 0);
    virtual ~ButtonsGroup();

    Ui::Button* getStartConversionButton();
    Ui::Button* getResetSettingsButton();
    Ui::Button* getSaveSettingsButton();
    Ui::Button* getClearConsoleButton();

private: // Buttons in group
    Ui::Button* startConvertion;
    Ui::Button* resetSettings;
    Ui::Button* saveSettings;
    Ui::Button* clearConsole;
    QVBoxLayout* layout;
};

}
#endif // BUTTONSGROUP_H
