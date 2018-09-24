#include "ButtonsGroup.h"

Ui::ButtonsGroup::ButtonsGroup(std::shared_ptr<management::ClientManager> clientManager, QWidget* parent) :
    QWidget(parent),
    startCalculation(new Ui::Button(clientManager, "Start Calculation")),
    launchParaview(new Ui::Button(clientManager, "Launch paraview")),
    stopCalculation(new Ui::Button(clientManager, "Stop Calculation")),
    clearConsole(new Ui::Button(clientManager, "Clear CONSOLE")),
    layout(new QVBoxLayout)
{
    layout->addWidget(startCalculation);
    layout->addWidget(launchParaview);
    layout->addWidget(stopCalculation);
    layout->addWidget(clearConsole);
    this->setLayout(layout);

    QObject::connect(clearConsole, SIGNAL(clicked()), clientManager.get(), SIGNAL(clearConsole()));
    QObject::connect(launchParaview, &Ui::Button::clicked, []()
    {
        auto wDir = management::FileManager::getInstance()->getWorkDir();
        if(!wDir.get()->path().isEmpty() && wDir.get()->path().toStdString() != ".")
        {
            logging::Logger::getInstance()->log(QString("paraFoam in ") + wDir.get()->path());
        }
    });

    QObject::connect(startCalculation, SIGNAL(clicked()), clientManager.get(), SIGNAL(disableUi()));
    QObject::connect(stopCalculation, SIGNAL(clicked()), clientManager.get(), SIGNAL(enableUi()));
    QObject::connect(stopCalculation, SIGNAL(clicked()), clientManager.get(), SIGNAL(stopCalculation()));

    QObject::connect(clientManager.get(), SIGNAL(disableUi()), startCalculation, SLOT(disable()));
    QObject::connect(clientManager.get(), SIGNAL(disableUi()), launchParaview, SLOT(disable()));
    QObject::connect(clientManager.get(), SIGNAL(disableUi()), clearConsole, SLOT(disable()));
    QObject::connect(clientManager.get(), SIGNAL(enableUi()), startCalculation, SLOT(enable()));
    QObject::connect(clientManager.get(), SIGNAL(enableUi()), launchParaview, SLOT(enable()));
    QObject::connect(clientManager.get(), SIGNAL(enableUi()), clearConsole, SLOT(enable()));

    QObject::connect(startCalculation, SIGNAL(clicked()), clientManager.get(), SLOT(startSyncMaps()));
}

Ui::Button* Ui::ButtonsGroup::ButtonsGroup::getStartConversionButton() {return startCalculation;}
Ui::Button* Ui::ButtonsGroup::ButtonsGroup::getResetSettingsButton()   {return launchParaview;}
Ui::Button* Ui::ButtonsGroup::ButtonsGroup::getStopConvertionButton()  {return stopCalculation;}
Ui::Button* Ui::ButtonsGroup::ButtonsGroup::getClearConsoleButton()    {return clearConsole;}

Ui::ButtonsGroup::~ButtonsGroup()
{
    delete startCalculation;
    delete launchParaview;
    delete stopCalculation;
    delete clearConsole;
    delete layout;
}
