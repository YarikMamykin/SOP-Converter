#ifndef BUTTONS_H
#define BUTTONS_H

#include <QPushButton>
#include <QPalette>
#include <QString>
#include <memory>
#include "../../logging/Logger/Logger.h"

namespace Ui
{

class Button : public QPushButton
{
    Q_OBJECT
public:
    explicit Button();
    explicit Button(QString name, QWidget* parent = 0);
    virtual ~Button();
public slots:
    void showMessage();
//    void setColor(Qt::GlobalColor color, Qt::GlobalColor fontColor = Qt::GlobalColor::black);
private:
    QPalette* pal; // left for setting background color
};

}
#endif // BUTTONS_H
