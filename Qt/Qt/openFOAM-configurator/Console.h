#ifndef CONSOLE_H
#define CONSOLE_H

#include <QObject>
#include <QString>
#include <QTextEdit>

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
public slots:
    void showLog(const QString& log);
};

}
#endif // CONSOLE_H
