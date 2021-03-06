#ifndef BUTTONSGROUP_H
#define BUTTONSGROUP_H

#include <QWidget>
#include <QVBoxLayout>
#include <memory>
#include <QProcess>
#include "Buttons.h"
#include "../../management/ClientManager/ClientManager.h"
#include "../../management/FileManager/FileManager.h"


namespace Ui
{

class ButtonsGroup : public QWidget
{
public:
    explicit ButtonsGroup(std::shared_ptr<management::ClientManager> clientManager, QWidget* parent = 0);
    virtual ~ButtonsGroup();

    Ui::Button* getStartConversionButton();
    Ui::Button* getResetSettingsButton();
    Ui::Button* getStopConvertionButton();
    Ui::Button* getClearConsoleButton();

private: // Buttons in group
    Ui::Button* startCalculation;
    Ui::Button* launchParaview;
    Ui::Button* stopCalculation;
    Ui::Button* clearConsole;
    QVBoxLayout* layout;
};

}
#endif // BUTTONSGROUP_H
