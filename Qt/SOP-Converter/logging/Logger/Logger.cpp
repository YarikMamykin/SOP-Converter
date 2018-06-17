#include "../../logging/Logger/Logger.h"

logging::Logger::Logger() :    
    fullLog(),
    currentDateTime(),
    dateTimeFormat("yyyy-dd-MM hh:mm:ss.zzz")
{

}

logging::Logger::~Logger()
{

}

logging::Logger* logging::Logger::getInstance()
{
    static logging::Logger instance;
    return &instance;
}

const QString logging::Logger::formatLog(const QString& log)
{    
    // format of log must be @Current date and time + log message@
    currentDateTime = QDateTime::currentDateTime();
    fullLog.clear();
    fullLog << currentDateTime.toString(dateTimeFormat);
    fullLog << "->";
    fullLog << log;
    return fullLog.join(" ");
}

bool logging::Logger::log(const QString& log, const logging::LogDirection& direction)
{
    if(direction == logging::LogDirection::file)
    {
        emit getInstance()->logToFile(formatLog(log));
    }
    else if(direction == logging::LogDirection::console)
    {
        emit getInstance()->logToConsole(formatLog(log));
    }
    else if(direction == logging::LogDirection::fileAndConsole)
    {
        emit getInstance()->logToFile(formatLog(log));
        emit getInstance()->logToConsole(formatLog(log));
    }

    return true;
}
