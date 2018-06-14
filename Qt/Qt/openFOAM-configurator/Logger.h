#ifndef LOGGER_H
#define LOGGER_H

#include <QObject>
#include <QFile>
#include <QDateTime>
#include <QStringList>
#include <memory>
#include <string>
#include <Console.h>

namespace logging
{

enum class LogDirection
{
    file = 1,
    console = 2,
    fileAndConsole = 3
};

/* Puts log into console or log file or both */
class Logger : public QObject
{
    Q_OBJECT
private:
    explicit Logger();
    explicit Logger(const Logger&) = delete;
    virtual ~Logger();

    const QString formatLog(const QString& log);
    void logToFile(const QString& log);

signals:
    void logToConsole(const QString& log);
public:
    static Logger* getInstance();
    bool log(const QString& log, const logging::LogDirection& direction = logging::LogDirection::fileAndConsole);
private:
    QFile logFile;
    QStringList fullLog;
    QDateTime currentDateTime;
    QString dateTimeFormat;
};

}
#endif // LOGGER_H

