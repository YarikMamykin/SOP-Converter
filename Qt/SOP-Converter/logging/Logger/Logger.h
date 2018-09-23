#ifndef LOGGER_H
#define LOGGER_H

#include <QObject>
#include "../../management/FileManager/FileManager.h"
#include "../../logging/Messanger/Messanger.h"
#include <QDateTime>
#include <QStringList>
#include <memory>
#include <string>

namespace logging
{

enum class LogDirection
{
    file = 1,
    console = 2,
    fileAndConsole = 3
};

/* Puts log into console or log file or both */
class Logger final : public QObject
{
    Q_OBJECT
private:
    explicit Logger();
    explicit Logger(const Logger&) = delete;
    virtual ~Logger();

private slots:
    const QString formatLog(const QString& log);
    void writeLogToFile(const QString& log);

signals:
    void logToConsole(const QString& log);
    void logToFile(const QString& log);
public:
    static logging::Logger* getInstance();
    bool log(const QString& log,
             const logging::LogDirection& direction = logging::LogDirection::fileAndConsole);
private:    
    QStringList fullLog;
    QDateTime currentDateTime;
    QString dateTimeFormat;
    std::shared_ptr<QFile> logFile;
    QMutex logFileLocker;
};

}
#endif // LOGGER_H

