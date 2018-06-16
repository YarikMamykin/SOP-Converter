#ifndef CONSOLEANDBUTTONSGROUP_H
#define CONSOLEANDBUTTONSGROUP_H

#include <QWidget>
#include <QVBoxLayout>
#include "../Buttons/ButtonsGroup.h"
#include "Console.h"

namespace Ui
{

class ConsoleAndButtonsGroup : public QWidget
{
public:
    explicit ConsoleAndButtonsGroup(QWidget* parent = 0);
    virtual ~ConsoleAndButtonsGroup();
private: // Buttons in group
    Ui::ButtonsGroup* buttons;
    Ui::Console* console;
    QHBoxLayout* layout;
};

}
#endif // CONSOLEANDBUTTONSGROUP_H
