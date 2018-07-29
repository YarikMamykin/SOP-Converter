#include "TransportPropertiesField.h"
#include "../../configuration/Parser/Parser.h"
#include "../../logging/Logger/Logger.h"
using LogManager = logging::Logger;
using Parser = configuration::Parser;
using ParserId = configuration::Parser::ParserId;

Ui::TransportPropertiesField::TransportPropertiesField(std::shared_ptr<configuration::ClientManager> cm, QWidget* parent) :
    QGroupBox(QString("-- Transport Properties --"),parent),
    clientManager(cm),
    tpUnit(),
    labels(),
    editFields(),
    tpMap(),
    layout(new QHBoxLayout)
{
    QObject::connect(clientManager.get(),
                     SIGNAL(notifyAll()),
                     this,
                     SLOT(loadMap()), Qt::QueuedConnection);
    QObject::connect(clientManager.get(),
                     SIGNAL(clearTpSets()),
                     this,
                     SLOT(reset()), Qt::QueuedConnection);
    QObject::connect(clientManager.get(),
                     SIGNAL(disableUi()),
                     this,
                     SLOT(disable()), Qt::QueuedConnection);

    for(auto e : tpDimensions)
    {
        tpMap.push_back(new std::pair<std::string, std::string>(e.toStdString(), std::string("")));
        labels.push_back(new QLabel(e));    (*(--labels.end()))->setAlignment(Qt::AlignCenter);

        if(e != *(--tpDimensions.end()))
        {
            editFields.push_back(new QSpinBox);
            dynamic_cast<QSpinBox*>(*(--editFields.end()))->setRange(-1000, 1000);
            dynamic_cast<QSpinBox*>(*(--editFields.end()))->setAlignment(Qt::AlignCenter);
        }else
        {
            editFields.push_back(new QDoubleSpinBox);
            dynamic_cast<QDoubleSpinBox*>(*(--editFields.end()))->setRange(0,1000);
            dynamic_cast<QDoubleSpinBox*>(*(--editFields.end()))->setSingleStep(0.01);
            dynamic_cast<QDoubleSpinBox*>(*(--editFields.end()))->setAlignment(Qt::AlignCenter);
        }

        tpUnit.push_back(new QVBoxLayout);
        (*(--tpUnit.end()))->addWidget(*(--labels.end()));
        (*(--tpUnit.end()))->addWidget(*(--editFields.end()));
        (*(--tpUnit.end()))->setSpacing(2);
        (*(--tpUnit.end()))->setAlignment(Qt::AlignCenter|Qt::AlignBottom);

        layout->addLayout(*(--tpUnit.end()));
    }

    this->layout->setSpacing(0);
    this->layout->setAlignment(Qt::AlignLeft);
    this->setLayout(this->layout);
}

Ui::TransportPropertiesField::~TransportPropertiesField()
{
    QObject::disconnect(this,0,0,0);
    for(int i = 0; i < 8; i++)
    {
        delete tpMap[i];
        delete labels[i];
        delete tpUnit[i];
        delete editFields[i];
    }
    delete layout;
}

void Ui::TransportPropertiesField::loadMap()
{
    LogManager::getInstance()->log("TransportProperties loading map");
    auto i = editFields.begin();
    for(auto e : tpMap)
    {
        e->second = Parser::getInstance()->getParserMap(ParserId::transportProperties).get()->find(e->first)->second;
        if(i != (--editFields.end()))
            dynamic_cast<QSpinBox*>(*i)->setValue(std::stoi(e->second));
        else
            dynamic_cast<QDoubleSpinBox*>(*i)->setValue(std::stod(e->second));
        ++i;
    }
}

void Ui::TransportPropertiesField::syncMap()
{

}

void Ui::TransportPropertiesField::reset()
{
    LogManager::getInstance()->log("TransportProperties reset");
    auto i = editFields.begin();
    for(auto e : tpMap)
    {
        if(e != *(--tpMap.end()))
            e->second = std::string("0");
        else
            e->second = std::string("0.00");

        if(i != (--editFields.end()))
            dynamic_cast<QSpinBox*>(*i)->setValue(std::stoi(e->second));
        else
            dynamic_cast<QDoubleSpinBox*>(*i)->setValue(std::stod(e->second));
        ++i;
    }
}

void Ui::TransportPropertiesField::disable()
{
    for(auto e : editFields)
    {
        e->setDisabled(true);
    }
}
