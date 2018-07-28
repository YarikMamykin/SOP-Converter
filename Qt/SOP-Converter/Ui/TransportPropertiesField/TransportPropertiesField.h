#ifndef TRANSPORTPROPERTIESFIELD_H
#define TRANSPORTPROPERTIESFIELD_H

#include <QObject>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QSpinBox>
#include <QLabel>
#include <QStringList>
#include <memory>
#include <vector>
#include "../../configuration/ClientManager/ClientManager.h"

namespace Ui
{

class TransportPropertiesField : public QHBoxLayout
{
    Q_OBJECT
public:
    explicit TransportPropertiesField(std::shared_ptr<configuration::ClientManager> cm);
    virtual ~TransportPropertiesField();
private slots:
    void syncMap();
private:
    std::shared_ptr<configuration::ClientManager> clientManager;
    std::vector<QVBoxLayout*> tpUnit;
    std::vector<QLabel*> labels;
    std::vector<QSpinBox*> editFields;
    std::vector<std::pair<std::string, std::string>*> tpMap;
};

}
#endif // TRANSPORTPROPERTIESFIELD_H
