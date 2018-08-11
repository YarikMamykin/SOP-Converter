#ifndef CONSOLE_H
#define CONSOLE_H

#include <QObject>
#include <QString>
#include <QTextEdit>
#include <QMutex>
#include <memory>
#include "../../logging/Logger/Logger.h"
#include "../../management/ClientManager/ClientManager.h"

namespace Ui
{

class Console : public QTextEdit
{
    Q_OBJECT
private:
    explicit Console(const Console&) = delete;
public:
    explicit Console(std::shared_ptr<management::ClientManager> cm);
    virtual ~Console();
private slots:
    void showLog(const QString& log);
private:
    QMutex consoleLocker;
    std::shared_ptr<management::ClientManager> clientManager;
};

}
#endif // CONSOLE_H
