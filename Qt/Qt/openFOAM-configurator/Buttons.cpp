#include "Buttons.h"
#include <QMessageBox>

Ui::OkButton::OkButton(QString name, QWidget* parent) :
    QPushButton(name, parent)
{
    QObject::connect(this, SIGNAL(clicked()), SLOT(showMessage()));
}

Ui::OkButton::~OkButton()
{
    QObject::disconnect(this, 0, 0, 0);
}

void Ui::OkButton::showMessage()
{
    QMessageBox msgBox;
    msgBox.setText("Name");
    msgBox.setInformativeText("Message from Ok button");
    msgBox.setStandardButtons(QMessageBox::Save | QMessageBox::Discard |
                              QMessageBox::Cancel);
    msgBox.setDefaultButton(QMessageBox::Save);
    msgBox.show();
    msgBox.exec();
}
