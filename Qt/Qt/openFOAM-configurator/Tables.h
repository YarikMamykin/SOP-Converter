#ifndef TABLES_H
#define TABLES_H
#include <QObject>
#include <QTableWidget>

namespace Ui
{

class SetTable : public QTableWidget
{
    Q_OBJECT
public:
    explicit SetTable(QWidget* parent = 0);
    virtual ~SetTable();

private:
    void setDefaultProperties();

};

}
#endif // TABLES_H
