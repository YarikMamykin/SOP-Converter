#ifndef TABLEANDETC_H
#define TABLEANDETC_H

#include <QWidget>
#include <QVBoxLayout>
#include "../Buttons/ButtonsGroup.h"
#include "Tables.h"

namespace Ui
{

class TableAndEtcGroup : public QWidget
{
public:
    explicit TableAndEtcGroup(QWidget* parent = 0);
    virtual ~TableAndEtcGroup();
private: // Buttons in group
    Ui::SetTable* table;
    // add another widgets if needs
    QHBoxLayout* layout;
};

}

#endif // TABLEANDETC_H
