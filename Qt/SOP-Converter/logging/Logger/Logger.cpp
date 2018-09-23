#include "../../logging/Logger/Logger.h"
#include <QDebug>

logging::Logger::Logger() :
    QObject(),
    fullLog(),
    currentDateTime(),
    dateTimeFormat("yyyy-dd-MM hh:mm:ss.zzz"),
    logFileLocker()
{
    logFile = management::FileManager::getInstance()->getLogFile();
    QObject::connect(this,
                     SIGNAL(logToFile(const QString&)),
                     SLOT(writeLogToFile(const QString&)), Qt::DirectConnection);
    writeLogToFile("Logger constructed");
}

logging::Logger::~Logger()
{
    writeLogToFile("Logger destructed");
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

void logging::Logger::writeLogToFile(const QString &log)
{
    logFileLocker.lock();
    if(logFile->open(QIODevice::Append|QIODevice::Text))
    {
        if(!logFile.get()->write((log + QString("\n")).toStdString().c_str()))
            logging::Messanger::getInstance()->showMessage(QString("file write didn't occur"));
        logFile.get()->close();
    } else {logging::Messanger::getInstance()->showMessage(QString("error opening file"));}
    logFileLocker.unlock();
}

bool logging::Logger::log(const QString& log, const logging::LogDirection& direction)
{
    if(direction == logging::LogDirection::file)
    {
        emit getInstance()->logToFile(formatLog(log));
    }
    else if(direction == logging::LogDirection::console)
    {
        emit getInstance()->logToConsole(QString("-> ") + log);
    }
    else if(direction == logging::LogDirection::fileAndConsole)
    {
        emit getInstance()->logToFile(formatLog(log));
        emit getInstance()->logToConsole(QString("-> ") + log);
    }

    return true;
}
