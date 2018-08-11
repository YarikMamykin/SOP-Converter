#ifndef TRANSPORTPROPERTIESFIELD_H
#define TRANSPORTPROPERTIESFIELD_H

#include <QObject>
#include <QThread>
#include <QGlobalStatic>
#include <QWidget>
#include <QGroupBox>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QDoubleSpinBox>
#include <QLabel>
#include <QStringList>
#include <memory>
#include <vector>
#include "../../management/ClientManager/ClientManager.h"

namespace Ui
{

class TransportPropertiesField : public QGroupBox
{
    Q_OBJECT
public:
    explicit TransportPropertiesField(std::shared_ptr<management::ClientManager> cm, QWidget* parent = 0);
    virtual ~TransportPropertiesField();
private slots:
    void loadMaps();
    void syncMaps();
    void reset();
    void disable();
    void enable();
private:
    std::shared_ptr<management::ClientManager> clientManager;
    std::vector<QVBoxLayout*> tpUnit;
    std::vector<QLabel*> labels;
    std::vector<QAbstractSpinBox*> editFields;
    std::vector<std::pair<std::string, std::string>*> tpMap;
    std::shared_ptr<std::vector<std::pair<std::string, std::string>*>> tpParserMap;
    QHBoxLayout* layout;
};

}
#endif // TRANSPORTPROPERTIESFIELD_H
