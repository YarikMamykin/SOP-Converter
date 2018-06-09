#ifndef LOGGER_H
#define LOGGER_H

#include <QObject>
#include <QFile>
#include <QDateTime>
#include <memory>
#include <string>
#include "Console.h"

namespace logging
{

class Logger : public QObject
{
    Q_OBJECT
private:
    explicit Logger();
    explicit Logger(const Logger&) = delete;
    virtual ~Logger();
signals:
    void logToConsole(const QString& log);
public:
    static Logger* getInstance();
    bool sendLogToFile(const QString& log);
    void sendLogToConsole(const QString& log);

private:
    QFile logFile;
};

}
#endif // LOGGER_H

