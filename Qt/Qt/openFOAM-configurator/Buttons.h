#ifndef BUTTONS_H
#define BUTTONS_H

#include <QPushButton>
#include <QString>

namespace Ui
{

class OkButton : public QPushButton
{
    Q_OBJECT
public:
    OkButton(QString name = "OK", QWidget* parent = 0);
    ~OkButton();

private slots:
    void showMessage();
};

}
#endif // BUTTONS_H
