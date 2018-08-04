#include "Tables.h"
#include "../../logging/Logger/Logger.h"
#include "../../configuration/Synchronizer/Synchronizer.h"
using LogManager = logging::Logger;
using Parser = configuration::Parser;
using ParserId = configuration::Parser::ParserId;
using Syncer = configuration::Synchronizer;
using SyncerThread = configuration::SynchronizerThread;

/* ---------------------------------------------------------------------- */
/* -- SetTable -- */
/* ---------------------------------------------------------------------- */

Ui::SetTable::SetTable(std::shared_ptr<configuration::ClientManager> clientManager, QWidget* parent) :
    QTableWidget(parent),
    cells(),
    pMap(Parser::getInstance()->getParserMap(ParserId::p)),
    uMap(Parser::getInstance()->getParserMap(ParserId::U)),
    boundaryMap(Parser::getInstance()->getParserMap(ParserId::boundary)),
    mapsLoaded(false),
    cellsErased(true)
{
    this->show();
    QObject::connect(clientManager.get(),
                     SIGNAL(notifyAll()),
                     this,
                     SLOT(loadMaps()), Qt::QueuedConnection);
    QObject::connect(this,
                     SIGNAL(cellChanged(int,int)),
                     SLOT(updateCellInfo(int,int)), Qt::DirectConnection);
    QObject::connect(clientManager.get(),
                     SIGNAL(disableUi()),
                     this,
                     SLOT(disable()), Qt::QueuedConnection);
    QObject::connect(clientManager.get(),
                     SIGNAL(enableUi()),
                     this,
                     SLOT(enable()), Qt::QueuedConnection);
    QObject::connect(clientManager.get(),
                     SIGNAL(syncMaps()),
                     this,
                     SLOT(syncMaps()), Qt::QueuedConnection);

    for(int i = 0; i < 5; i++)
    {
        cells.push_back(new std::vector<Cell*>());
    }
    LogManager::getInstance()->log("SetTable created");
}

Ui::SetTable::~SetTable()
{
    this->hide();
    QObject::disconnect(this,0,0,0);
    for(auto e : cells)
    {
        for(auto c : *e)
        {
            delete c;
        }
        e->clear();
        delete e;
    }
    LogManager::getInstance()->log("SetTable destroyed");
}

void Ui::SetTable::syncMaps()
{
    LogManager::getInstance()->log("Synchronize maps :: SetTable");

    SyncerThread sthreadP(new Syncer([this]()
    {
        auto iter = cells[static_cast<int>(Column::value_p)]->begin();
        auto buffer = pMap.get()->begin();

        for(auto e : *cells[static_cast<int>(Column::type_p)])
        {
            buffer = pMap.get()->find(e->getMapIndexPatchName());
            buffer->second = e->getMapIndexPatchTypeValue();
            if((*iter)->getMapIndexPatchTypeValue() != std::string("-"))
            {
                buffer->second.append(std::string(" ") + (*iter)->getMapIndexPatchTypeValue());
            }
            ++iter;
        }

        for(auto e : *this->pMap.get())
        {
            LogManager::getInstance()->log(QString("%1 === %2").
                                           arg(e.first.c_str()).
                                           arg(e.second.c_str()));
        }
    }, static_cast<int>(ParserId::p)));
    SyncerThread sthreadU(new Syncer([this]()
    {
        auto iter = cells[static_cast<int>(Column::value_U)]->begin();
        auto buffer = uMap.get()->begin();

        for(auto e : *cells[static_cast<int>(Column::type_U)])
        {
            buffer = uMap.get()->find(e->getMapIndexPatchName());
            buffer->second = e->getMapIndexPatchTypeValue();
            if((*iter)->getMapIndexPatchTypeValue() != std::string("-"))
            {
                buffer->second.append(std::string(" ") + (*iter)->getMapIndexPatchTypeValue());
            }
            ++iter;
        }

        for(auto e : *this->uMap.get())
        {
            LogManager::getInstance()->log(QString("%1 === %2").
                                           arg(e.first.c_str()).
                                           arg(e.second.c_str()));
        }
    }, static_cast<int>(ParserId::U)));
    SyncerThread sthreadB(new Syncer([this]()
    {
        for(auto e : *cells[static_cast<int>(Column::type_boundary)])
        {
            boundaryMap.get()->find(e->getMapIndexPatchName())->second = e->getMapIndexPatchTypeValue();
        }

        for(auto e : *this->boundaryMap.get())
        {
            LogManager::getInstance()->log(QString("%1 === %2").
                                           arg(e.first.c_str()).
                                           arg(e.second.c_str()));
        }
    }, static_cast<int>(ParserId::boundary)));

    emit sthreadP.start();
    emit sthreadU.start();
    emit sthreadB.start();
}

void Ui::SetTable::loadMaps()
{
    LogManager::getInstance()->log("Loading maps");
    mapsLoaded = false;
    this->erase();
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
    this->horizontalHeader()->show();
    this->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    this->verticalHeader()->show();
    this->verticalScrollBar()->show();

    this->show();
    mapsLoaded = true;
    cellsErased = false;
}

void Ui::SetTable::updateCellInfo(int row, int column)
{
    if(!mapsLoaded || cellsErased) return;

    for(auto e : *cells[column])
    {
        if(e->getTableIndexRow() == row)
        {
            e->updateValue();
            LogManager::getInstance()->log(QString("Cell updated [ %1 ; %2 ]").
                                           arg(e->getMapIndexPatchName().c_str()).
                                           arg(this->model()->headerData(column, Qt::Horizontal).toString()));
            break;
        }
    }
}

void Ui::SetTable::eraseCells()
{
    for(auto e : cells)
    {
        if(e->size() == 0) return;
        for(auto c : *e)
        {
            delete c;
        }
        e->clear();
    }
    cellsErased = true;
    LogManager::getInstance()->log(QString("Cells erased = ") + boolToString(cellsErased));
}

void Ui::SetTable::erase()
{
    QObject::disconnect(this,
                        SIGNAL(cellChanged(int,int)),
                        this,
                        SLOT(updateCellInfo(int,int)));
    eraseCells();
    this->clear();
    this->setRowCount(0);
    this->setColumnCount(0);
    this->horizontalHeader()->hide();
    this->verticalHeader()->hide();
    QObject::connect(this,
                     SIGNAL(cellChanged(int,int)),
                     SLOT(updateCellInfo(int,int)), Qt::DirectConnection);
}

void Ui::SetTable::disable()
{
    this->setDisabled(true);
}

void Ui::SetTable::enable()
{
    this->setDisabled(false);
}

/* ---------------------------------------------------------------------- */
/* -- ControlDictTable -- */
/* ---------------------------------------------------------------------- */

Ui::ControlDictTable::ControlDictTable(std::shared_ptr<configuration::ClientManager> clientManager, QWidget* parent) :
    QTableWidget(parent),
    cells(),
    controlDictMap(Parser::getInstance()->getParserMap(ParserId::controlDict)),
    mapsLoaded(false),
    cellsErased(true)
{
    this->show();
    QObject::connect(clientManager.get(),
                     SIGNAL(notifyAll()),
                     this,
                     SLOT(loadMaps()), Qt::QueuedConnection);
    QObject::connect(this,
                     SIGNAL(cellChanged(int,int)),
                     SLOT(updateCellInfo(int,int)), Qt::DirectConnection);
    QObject::connect(clientManager.get(),
                     SIGNAL(disableUi()),
                     this,
                     SLOT(disable()), Qt::QueuedConnection);
    QObject::connect(clientManager.get(),
                     SIGNAL(enableUi()),
                     this,
                     SLOT(enable()), Qt::QueuedConnection);
    QObject::connect(clientManager.get(),
                     SIGNAL(syncMaps()),
                     this,
                     SLOT(syncMaps()), Qt::QueuedConnection);

    LogManager::getInstance()->log("ControlDictTable created");
}

Ui::ControlDictTable::~ControlDictTable()
{
    this->hide();
    QObject::disconnect(this,0,0,0);
    for(auto e : cells)
    {
        delete e;
    }
    cells.clear();
    LogManager::getInstance()->log("ControlDictTable destroyed");
}

void Ui::ControlDictTable::syncMaps()
{
    LogManager::getInstance()->log("Synchronize maps :: ControlDictTable");

    SyncerThread sthread(new Syncer([this]()
    {
        for(auto e : cells)
        {
            controlDictMap.get()->find(e->getMapIndexPatchName())->second = e->getMapIndexPatchTypeValue();
        }

        for(auto e : *this->controlDictMap.get())
        {
            LogManager::getInstance()->log(QString("%1 === %2").
                                           arg(e.first.c_str()).
                                           arg(e.second.c_str()));
        }
    }, static_cast<int>(ParserId::controlDict)));

    emit sthread.start();
}

void Ui::ControlDictTable::loadMaps()
{
    LogManager::getInstance()->log("Loading maps");
    mapsLoaded = false;
    this->erase();
    QStringList labels;
    labels << "Value";

    for(int i = 0; i < labels.size(); i++)
    {
        this->insertColumn(i);
    }
    this->setHorizontalHeaderLabels(labels);

    labels.clear();
    int i = 0;
    for(auto e : *controlDictMap.get())
    {
        labels << e.first.c_str();
        cells.push_back(new Cell(i,
                                 0,
                                 e.first,
                                 e.second));
        this->insertRow(i++);
    }
    this->setVerticalHeaderLabels(labels);

    // ------ //

    labels.clear();
    i = 0;
    for(auto e : cells)
    {
       this->setItem(i++, 0, e->getInstance());
    }

    this->resizeColumnsToContents();
    this->resizeRowsToContents();
    this->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    this->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    this->horizontalHeader()->show();
    this->verticalHeader()->show();

    this->show();
    mapsLoaded = true;
    cellsErased = false;
}

void Ui::ControlDictTable::updateCellInfo(int row, int column)
{
    if(!mapsLoaded || cellsErased) return;

    for(auto e : cells)
    {
        if(e->getTableIndexRow() == row)
        {
            e->updateValue();
            LogManager::getInstance()->log(QString("Cell updated [ %1 ; %2 ]").
                                           arg(e->getMapIndexPatchName().c_str()).
                                           arg(this->model()->headerData(column, Qt::Horizontal).toString()));
            break;
        }
    }
}

void Ui::ControlDictTable::eraseCells()
{
    for(auto e : cells)
    {
        delete e;
    }
    cells.clear();
    cellsErased = true;
    LogManager::getInstance()->log(QString("Cells erased = ") + boolToString(cellsErased));
}

void Ui::ControlDictTable::erase()
{
    QObject::disconnect(this,
                        SIGNAL(cellChanged(int,int)),
                        this,
                        SLOT(updateCellInfo(int,int)));
    eraseCells();
    this->clear();
    this->setRowCount(0);
    this->setColumnCount(0);
    this->horizontalHeader()->hide();
    this->verticalHeader()->hide();
    QObject::connect(this,
                     SIGNAL(cellChanged(int,int)),
                     SLOT(updateCellInfo(int,int)), Qt::DirectConnection);
}

void Ui::ControlDictTable::disable()
{
    this->setDisabled(true);
}

void Ui::ControlDictTable::enable()
{
    this->setDisabled(false);
}
