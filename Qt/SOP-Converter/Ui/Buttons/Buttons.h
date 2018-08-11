#ifndef BUTTONS_H
#define BUTTONS_H

#include <QPushButton>
#include <QPalette>
#include <QString>
#include <memory>
#include "../../logging/Logger/Logger.h"
#include "../../management/ClientManager/ClientManager.h"

namespace Ui
{

class Button : public QPushButton
{
    Q_OBJECT
public:
    explicit Button(std::shared_ptr<management::ClientManager> cm, QString name, QWidget* parent = 0);
    virtual ~Button();
public slots:
    void showMessage();
    void disable();
    void enable();
//    void setColor(Qt::GlobalColor color, Qt::GlobalColor fontColor = Qt::GlobalColor::black);
private:
    QPalette* pal; // left for setting background color
    std::shared_ptr<management::ClientManager> clientManager;
};

}
#endif // BUTTONS_H
