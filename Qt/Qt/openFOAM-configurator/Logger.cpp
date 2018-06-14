#include <Logger.h>
#include <Messanger.h>

logging::Logger::Logger() :
    logFile(),
    fullLog(),
    currentDateTime(),
    dateTimeFormat("yyyy-dd-MM hh:mm:ss.zzz")
{
    int fileNumber = 0;
    QString filePath("/tmp/LOG");
    do
    {
        logFile.setFileName
                (
                    QString().sprintf("%s%d", filePath.toStdString().c_str(), fileNumber)
                );
        fileNumber++;
    }while(logFile.exists());

    // create file
    if(!logFile.open(QIODevice::Append|QIODevice::Text))
    {
        logging::Messanger::getInstance()->showMessage(QString("Couldn't open log file"));
    }
    logFile.close();
}

logging::Logger::~Logger()
{
    logFile.close();
}

logging::Logger* logging::Logger::getInstance()
{
    static Logger instance;
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

void logging::Logger::logToFile(const QString &log)
{
    if(logFile.open(QIODevice::Append|QIODevice::Text))
    {
        if(!logFile.write((log + QString("\n")).toStdString().c_str()))
            logging::Messanger::getInstance()->showMessage(QString("file write didn't occur"));
        logFile.close();
    } else {logging::Messanger::getInstance()->showMessage(QString("error opening file"));}
}

bool logging::Logger::log(const QString& log, const logging::LogDirection& direction)
{
    if(direction == logging::LogDirection::file)
    {
        logToFile(formatLog(log));
    }
    else if(direction == logging::LogDirection::console)
    {
        emit getInstance()->logToConsole(formatLog(log));
    }
    else if(direction == logging::LogDirection::fileAndConsole)
    {
        logToFile(formatLog(log));
        emit getInstance()->logToConsole(formatLog(log));
    }

    return true;
}
