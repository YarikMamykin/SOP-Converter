#ifndef TABLES_H
#define TABLES_H
#include <QObject>
#include <QTableWidget>
#include <QHeaderView>
#include <QScrollBar>
#include <memory>
#include "../../configuration/Parser/Parser.h"

namespace Ui
{

class SetTable : public QTableWidget
{
    Q_OBJECT
public:
    explicit SetTable(QWidget* parent = 0);
    virtual ~SetTable();

private slots:
    void setDefaultProperties();
    void loadMaps();
private:
    std::shared_ptr<std::map<std::string, std::string>> pMap;
    std::shared_ptr<std::map<std::string, std::string>> uMap;
    std::shared_ptr<std::map<std::string, std::string>> boundaryMap;
};

}
#endif // TABLES_H
