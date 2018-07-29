#ifndef TRANSPORTPROPERTIESFIELD_H
#define TRANSPORTPROPERTIESFIELD_H

#include <QObject>
#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QDoubleSpinBox>
#include <QLabel>
#include <QStringList>
#include <memory>
#include <vector>
#include "../../configuration/ClientManager/ClientManager.h"

namespace Ui
{

class TransportPropertiesField : public QWidget
{
    Q_OBJECT
public:
    explicit TransportPropertiesField(std::shared_ptr<configuration::ClientManager> cm, QWidget* parent = 0);
    virtual ~TransportPropertiesField();
private slots:
    void loadMap();
    void syncMap();
    void reset();
private:
    std::shared_ptr<configuration::ClientManager> clientManager;
    std::vector<QVBoxLayout*> tpUnit;
    std::vector<QLabel*> labels;
    std::vector<QAbstractSpinBox*> editFields;
    std::vector<std::pair<std::string, std::string>*> tpMap;
    QHBoxLayout* layout;
};

}
#endif // TRANSPORTPROPERTIESFIELD_H
