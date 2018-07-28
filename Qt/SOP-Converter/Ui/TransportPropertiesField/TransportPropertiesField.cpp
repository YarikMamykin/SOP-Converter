#include "TransportPropertiesField.h"

Ui::TransportPropertiesField::TransportPropertiesField(std::shared_ptr<configuration::ClientManager> cm) :
    clientManager(cm),
    tpUnit(),
    labels(),
    editFields(),
    tpMap()
{
    QStringList keys;
    keys << "kg"
         << "m"
         << "s"
         << "K"
         << "kgmol"
         << "A"
         << "cd"
         << "viscosity";
    for(auto e : keys)
    {
        tpMap.push_back(new std::pair<std::string, std::string>(e.toStdString(), std::string("")));
        labels.push_back(new QLabel(e));
        this->addWidget(labels[labels.size() - 1]);
        labels[labels.size() - 1]->show();
    }
}

Ui::TransportPropertiesField::~TransportPropertiesField()
{
//    for(int i = 0; i < 8; i++)
//    {
//        delete labels[i];
//        delete tpUnit[i];
//        delete editFields[i];
//        delete tpMap[i];
//    }
}

void Ui::TransportPropertiesField::syncMap()
{

}
