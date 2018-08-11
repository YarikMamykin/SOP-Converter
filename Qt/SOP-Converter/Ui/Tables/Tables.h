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
#include "../../management/ClientManager/ClientManager.h"

namespace Ui
{

class Cell : public QObject
{
    // must receive signals from table about change and
    // sync changes accordingly to both maps: table and parser
    Q_OBJECT
public:
    explicit Cell(unsigned int row, unsigned int col, std::string patch, std::string value);
    virtual ~Cell();
    /* set */
    void setTableIndexRow(const int& row);
    void setTableIndexColumn(const int& column);
    void setMapIndexPatchName(const std::string& patchName);
    void setMapIndexPatchTypeValue(const std::string& patchTypeValue);
    /* get */
    int getTableIndexRow();
    int getTableIndexColumn();
    std::string getMapIndexPatchName();
    std::string getMapIndexPatchTypeValue();
    QTableWidgetItem* getInstance();
    /* update */
    void updateValue();
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
    explicit SetTable(std::shared_ptr<management::ClientManager> clientManager, QWidget* parent = 0);
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
    std::shared_ptr<std::vector<std::pair<std::string, std::string>*>> pMap;
    std::shared_ptr<std::vector<std::pair<std::string, std::string>*>> uMap;
    std::shared_ptr<std::vector<std::pair<std::string, std::string>*>> boundaryMap;

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
    explicit ControlDictTable(std::shared_ptr<management::ClientManager> clientManager, QWidget* parent = 0);
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
    std::shared_ptr<std::vector<std::pair<std::string, std::string>*>> controlDictMap;
    std::shared_ptr<management::ClientManager> cm;

    bool mapsLoaded;
    bool cellsErased;
};

}

#endif // TABLES_H
