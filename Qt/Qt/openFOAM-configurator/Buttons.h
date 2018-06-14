#ifndef BUTTONS_H
#define BUTTONS_H

#include <QPushButton>
#include <QString>
#include <Messanger.h>

namespace Ui
{

class StartConvertionButton : public QPushButton
{
    Q_OBJECT
public:
    StartConvertionButton(QString name = "Start Convertion", QWidget* parent = 0);
    ~StartConvertionButton();

private slots:
    void showMessage();
};

class ResetSettingsButton : public QPushButton
{
    Q_OBJECT
public:
    ResetSettingsButton(QString name = "Reset settings", QWidget* parent = 0);
    ~ResetSettingsButton();

private slots:
    void showMessage();
};

class SaveSettingsButton : public QPushButton
{
    Q_OBJECT
public:
    SaveSettingsButton(QString name = "Save settings", QWidget* parent = 0);
    ~SaveSettingsButton();

private slots:
    void showMessage();
};

}
#endif // BUTTONS_H
