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
private: // Buttons in group
    Ui::Button* startConvertion;
    Ui::Button* resetSettings;
    Ui::Button* saveSettings;
    QVBoxLayout* layout;
};

}
#endif // BUTTONSGROUP_H
