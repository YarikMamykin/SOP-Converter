#ifndef CONSOLE_H
#define CONSOLE_H

#include <QObject>
#include <QString>
#include <QTextEdit>
#include <memory>
#include "../../logging/Logger/Logger.h"

namespace Ui
{

class Console : public QTextEdit // MAKE IT SINGLETON FOR LOGGER!!!
{
    Q_OBJECT
private:
    explicit Console(const Console&) = delete;
public:
    explicit Console();
    virtual ~Console();
private slots:
    void showLog(const QString& log);
private:
};

}
#endif // CONSOLE_H
