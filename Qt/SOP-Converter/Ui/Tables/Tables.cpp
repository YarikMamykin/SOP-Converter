#include "Tables.h"
#include "../../logging/Logger/Logger.h"
using LogManager = logging::Logger;
using Parser = configuration::Parser;
using ParserId = configuration::Parser::ParserId;

Ui::SetTable::SetTable(QWidget* parent) :
    QTableWidget(parent),
    newItem(new QTableWidgetItem("kek")),
    pMap(Parser::getInstance()->getParserMap(ParserId::p)),
//    pCells(),
    uMap(Parser::getInstance()->getParserMap(ParserId::U)),
//    uCells(),
    boundaryMap(Parser::getInstance()->getParserMap(ParserId::boundary))

//    boundaryCells()
{
    setDefaultProperties();
    QObject::connect(configuration::Parser::getInstance(),
                     SIGNAL(notifyAll()),
                     this,
                     SLOT(loadMaps()), Qt::QueuedConnection);
}

Ui::SetTable::~SetTable()
{
    this->hide();
    QObject::disconnect(configuration::Parser::getInstance(),
                        SIGNAL(notifyAll()),
                        this,
                        SLOT(Ui::SetTable::loadMaps()));
    delete newItem;
//    for(auto e : pCells)
//    {
//        delete e;
//    }
//    pCells.clear();
//    for(auto e : uCells)
//    {
//        delete e;
//    }
//    uCells.clear();
//    for(auto e : boundaryCells)
//    {
//        delete e;
//    }
//    boundaryCells.clear();
}

void Ui::SetTable::setDefaultProperties()
{
    this->show();
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
        this->insertRow(i++);
    }

    // ------ //

    this->setVerticalHeaderLabels(labels);

    this->resizeColumnsToContents();
    this->resizeRowsToContents();
    this->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    this->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    this->verticalScrollBar()->show();

    this->show();
    newItem->setText(pMap.get()->find("back")->second.c_str());
    this->setItem(0,0,newItem);
}
