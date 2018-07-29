#ifndef TABLEANDETC_H
#define TABLEANDETC_H

#include <QWidget>
#include <QVBoxLayout>
#include "../Buttons/ButtonsGroup.h"
#include "Tables.h"
#include "configuration/ClientManager/ClientManager.h"
#include "Ui/TransportPropertiesField/TransportPropertiesField.h"

namespace Ui
{

class TableAndEtcGroup : public QWidget
{
public:
    explicit TableAndEtcGroup(std::shared_ptr<configuration::ClientManager> clientManager, QWidget* parent = 0);
    virtual ~TableAndEtcGroup();
private:
    Ui::SetTable* table;
//    Ui::TransportPropertiesField* tpField;
    // add another widgets if needs
    QHBoxLayout* layout;    
};

}

#endif // TABLEANDETC_H
