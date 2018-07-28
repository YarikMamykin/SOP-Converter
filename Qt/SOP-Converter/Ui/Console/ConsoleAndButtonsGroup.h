#ifndef CONSOLEANDBUTTONSGROUP_H
#define CONSOLEANDBUTTONSGROUP_H

#include <QWidget>
#include <QVBoxLayout>
#include "../Buttons/ButtonsGroup.h"
#include "Console.h"
#include "../../configuration/ClientManager/ClientManager.h"

namespace Ui
{

class ConsoleAndButtonsGroup : public QWidget
{
public:
    explicit ConsoleAndButtonsGroup(std::shared_ptr<configuration::ClientManager> clientManager, QWidget* parent = 0);
    virtual ~ConsoleAndButtonsGroup();
private: // Buttons in group
    Ui::ButtonsGroup* buttons;
    Ui::Console* console;
    QHBoxLayout* layout;
};

}
#endif // CONSOLEANDBUTTONSGROUP_H
