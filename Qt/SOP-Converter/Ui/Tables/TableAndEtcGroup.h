#ifndef TABLEANDETC_H
#define TABLEANDETC_H

#include <QWidget>
#include <QVBoxLayout>
#include "../Buttons/ButtonsGroup.h"
#include "Tables.h"
#include "management/ClientManager/ClientManager.h"
#include "Ui/TransportPropertiesField/TransportPropertiesField.h"

namespace Ui
{

class TableAndEtcGroup : public QWidget
{
public:
    explicit TableAndEtcGroup(std::shared_ptr<management::ClientManager> clientManager, QWidget* parent = 0);
    virtual ~TableAndEtcGroup();
private:
    Ui::SetTable* table;
    Ui::ControlDictTable* cdTable;
    QHBoxLayout* layout;    
};

}

#endif // TABLEANDETC_H
