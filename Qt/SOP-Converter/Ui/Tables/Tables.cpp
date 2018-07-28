#include "Tables.h"
#include "../../logging/Logger/Logger.h"
using LogManager = logging::Logger;
using Parser = configuration::Parser;
using ParserId = configuration::Parser::ParserId;

Ui::SetTable::SetTable(std::shared_ptr<configuration::ClientManager> clientManager, QWidget* parent) :
    QTableWidget(parent),
    cells(),
    pMap(Parser::getInstance()->getParserMap(ParserId::p)),
    uMap(Parser::getInstance()->getParserMap(ParserId::U)),
    boundaryMap(Parser::getInstance()->getParserMap(ParserId::boundary)),
    cm(clientManager),
    mapsLoaded(false)
{
    this->show();
    QObject::connect(configuration::Parser::getInstance(),
                     SIGNAL(notifyAll()),
                     this,
                     SLOT(loadMaps()), Qt::DirectConnection);
    QObject::connect(this,
                     SIGNAL(cellChanged(int,int)),
                     SLOT(updateCellInfo(int,int)), Qt::DirectConnection);

    for(int i = 0; i < 5; i++)
    {
        cells.push_back(new std::vector<Cell*>());
    }
    LogManager::getInstance()->log("Table created");
}

Ui::SetTable::~SetTable()
{
    this->hide();
    QObject::disconnect(configuration::Parser::getInstance(),
                        SIGNAL(notifyAll()),
                        this,
                        SLOT(loadMaps()));
    QObject::disconnect(this,
                        SIGNAL(cellChanged(int,int)),
                        this,
                        SLOT(updateCellInfo(int,int)));

    for(auto e : cells)
    {
        for(auto c : *e)
        {
            delete c;
        }
        delete e;
    }
    LogManager::getInstance()->log("Table destroyed");
}

void Ui::SetTable::setDefaultProperties()
{

}

void Ui::SetTable::loadMaps()
{
    QStringList labels;
    labels << "type (p)"
           << "value (p)"
           << "type (U)"
           << "value (U)"
           << "type (boundary)";

    for(int i = 0; i < labels.size(); i++)
    {
        this->insertColumn(i);
    }
    this->setHorizontalHeaderLabels(labels);

    labels.clear();
    int i = 0;
    for(auto e : *boundaryMap.get())
    {
        labels << e.first.c_str();    
        cells[static_cast<int>(SetTable::Column::type_boundary)]->push_back(new Cell(i,
                                                                                     static_cast<unsigned int>(SetTable::Column::type_boundary),
                                                                                     e.first,
                                                                                     e.second));
        this->insertRow(i++);
    }
    this->setVerticalHeaderLabels(labels);

    // ------ //

    labels.clear();
    QString buffer;
    i = 0;
    for(auto e : *pMap.get())
    {
        buffer = QString(e.second.c_str());
        if(buffer.contains(" "))
        {
            labels.clear();
            labels = buffer.split(" ");
            cells[static_cast<int>(SetTable::Column::type_p)]->push_back(new Cell(i,
                                                                                  static_cast<int>(SetTable::Column::type_p),
                                                                                  e.first,
                                                                                  labels[0].toStdString()));
            cells[static_cast<int>(SetTable::Column::value_p)]->push_back(new Cell(i,
                                                                                  static_cast<int>(SetTable::Column::value_p),
                                                                                  e.first,
                                                                                  labels[1].toStdString()));
        }
        else
        {
            cells[static_cast<int>(SetTable::Column::type_p)]->push_back(new Cell(i,
                                                                                  static_cast<int>(SetTable::Column::type_p),
                                                                                  e.first,
                                                                                  e.second));
            cells[static_cast<int>(SetTable::Column::value_p)]->push_back(new Cell(i,
                                                                                  static_cast<int>(SetTable::Column::value_p),
                                                                                  e.first,
                                                                                  std::string("-")));
        }
        i++;
    }

    i = 0;
    for(auto e : *uMap.get())
    {
        buffer = QString(e.second.c_str());
        if(buffer.contains(" "))
        {
            labels.clear();
            labels = buffer.split(" ");
            cells[static_cast<int>(SetTable::Column::type_U)]->push_back(new Cell(i,
                                                                                  static_cast<int>(SetTable::Column::type_U),
                                                                                  e.first,
                                                                                  labels[0].toStdString()));
            cells[static_cast<int>(SetTable::Column::value_U)]->push_back(new Cell(i,
                                                                                  static_cast<int>(SetTable::Column::value_U),
                                                                                  e.first,
                                                                                  buffer.toStdString().substr(buffer.indexOf('('), buffer.indexOf(')') - buffer.indexOf('(') + 1)));
        }
        else
        {
            cells[static_cast<int>(SetTable::Column::type_U)]->push_back(new Cell(i,
                                                                                  static_cast<int>(SetTable::Column::type_U),
                                                                                  e.first,
                                                                                  e.second));
            cells[static_cast<int>(SetTable::Column::value_U)]->push_back(new Cell(i,
                                                                                  static_cast<int>(SetTable::Column::value_U),
                                                                                  e.first,
                                                                                  std::string("-")));
        }
        i++;
    }

    int n = 0;
    for(auto e : cells)
    {
        i = 0;
        for(auto c : *e)
        {
            this->setItem(i++, n, c->getInstance());
        }
        n++;
    }

    this->resizeColumnsToContents();
    this->resizeRowsToContents();
    this->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    this->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    this->verticalScrollBar()->show();

    this->show();
    mapsLoaded = true;
}

void Ui::SetTable::updateCellInfo(int row, int column)
{
    if(!mapsLoaded) return;
    LogManager::getInstance()->log(QString("mapsLoaded = ") + boolToString(mapsLoaded));

    for(auto e : *cells[column])
    {
        if(e->getTableIndexRow() == row)
        {
            e->updateValue();
            LogManager::getInstance()->log(QString("Cell updated [ %1 ; %2 ]").arg(e->getMapIndexPatchName().c_str()).arg(this->model()->headerData(column, Qt::Horizontal).toString()));
            break;
        }
    }
}
