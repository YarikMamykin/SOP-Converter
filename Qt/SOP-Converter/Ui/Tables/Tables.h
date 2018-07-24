#ifndef TABLES_H
#define TABLES_H
#include <QObject>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QHeaderView>
#include <QScrollBar>
#include <memory>
#include <map>
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
//    class Cell;
    QTableWidgetItem* newItem;
    std::shared_ptr<std::map<std::string, std::string>> pMap;
//    std::vector<Cell*> pCells;
    std::shared_ptr<std::map<std::string, std::string>> uMap;
//    std::vector<Cell*> uCells;
    std::shared_ptr<std::map<std::string, std::string>> boundaryMap;
//    std::vector<Cell*> boundaryCells;
};

//class SetTable::Cell : public QTableWidgetItem
//{
//    // must receive signals from table about change and
//    // sync changes accordingly to both maps: table and parser
//    Q_OBJECT
//public:
//    explicit Cell();
//    explicit Cell(int col, int row, std::string patch, std::string value);
//    virtual ~Cell();
//    void setTableIndexColumn(int column);
//    void setTableIndexRow(int row);
//    void setMapIndexPatchName(std::string patchName);
//    void setMapIndexPatchTypeValue(std::string patchTypeValue);
//private:
//    std::pair<int, int> tableIndex;
//    std::pair<std::string, std::string> mapIndex;
//};

}

#endif // TABLES_H
