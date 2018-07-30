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
#include "../../configuration/ClientManager/ClientManager.h"

namespace Ui
{

class Cell : public QObject
{
    // must receive signals from table about change and
    // sync changes accordingly to both maps: table and parser
    Q_OBJECT
public:
    explicit Cell(unsigned int row, unsigned int col, std::string patch, std::string value) :
        tableIndex(row, col),
        mapIndex(patch, value),
        instance(new QTableWidgetItem(value.c_str()))
    {
        instance->setTextAlignment(Qt::AlignCenter);
    }
    virtual ~Cell()
    {
        if(instance) delete instance;
    }
    /* set */
    void setTableIndexRow(const int& row)                             {tableIndex.first = row;}
    void setTableIndexColumn(const int& column)                       {tableIndex.second = column;}
    void setMapIndexPatchName(const std::string& patchName)           {mapIndex.first = patchName;}
    void setMapIndexPatchTypeValue(const std::string& patchTypeValue) {mapIndex.second = patchTypeValue;}
    /* get */
    int getTableIndexRow()                  {return tableIndex.first;}
    int getTableIndexColumn()               {return tableIndex.second;}
    std::string getMapIndexPatchName()      {return mapIndex.first;}
    std::string getMapIndexPatchTypeValue() {return mapIndex.second;}
    QTableWidgetItem* getInstance()         {return instance;}
    /* update */
    void updateValue() { mapIndex.second = this->instance->text().toStdString(); }
private:
    std::pair<int, int> tableIndex;
    std::pair<std::string, std::string> mapIndex;
    QTableWidgetItem* instance;
};

/* ---------------------------------------------------------------------- */
/* -- SetTable -- */
/* ---------------------------------------------------------------------- */

class SetTable : public QTableWidget
{
    Q_OBJECT
public:
    explicit SetTable(std::shared_ptr<configuration::ClientManager> clientManager, QWidget* parent = 0);
    virtual ~SetTable();

private slots:
    void syncMaps();
    void loadMaps();
    void updateCellInfo(int row, int column);
    void eraseCells();
    void erase();
    void disable();
    void enable();
private:    
    enum class Column { type_p, value_p, type_U, value_U, type_boundary };

    std::vector<std::vector<Cell*>*> cells;    
    std::shared_ptr<std::map<std::string, std::string>> pMap;
    std::shared_ptr<std::map<std::string, std::string>> uMap;
    std::shared_ptr<std::map<std::string, std::string>> boundaryMap;

    bool mapsLoaded;
    bool cellsErased;
};

/* ---------------------------------------------------------------------- */
/* -- ControlDictTable -- */
/* ---------------------------------------------------------------------- */

class ControlDictTable : public QTableWidget
{
    Q_OBJECT
public:
    explicit ControlDictTable(std::shared_ptr<configuration::ClientManager> clientManager, QWidget* parent = 0);
    virtual ~ControlDictTable();
private slots:
    void syncMaps();
    void loadMaps();
    void updateCellInfo(int row, int column);
    void eraseCells();
    void erase();
    void disable();
    void enable();
private:
    std::vector<Cell*> cells;
    std::shared_ptr<std::map<std::string, std::string>> controlDictMap;
    std::shared_ptr<configuration::ClientManager> cm;

    bool mapsLoaded;
    bool cellsErased;
};

}

#endif // TABLES_H
