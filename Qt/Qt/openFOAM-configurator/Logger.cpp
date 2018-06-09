#include <Logger.h>

logging::Logger::Logger() :
    logFile()
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
    if(!logFile.open(QIODevice::WriteOnly))
    {

    }


}

logging::Logger::~Logger()
{

}

logging::Logger* logging::Logger::getInstance()
{
    static Logger instance;
    return &instance;
}

void logging::Logger::sendLogToConsole(const QString& log)
{
    // format of log must be @Current date and time + log message@
    emit getInstance()->logToConsole(log);
}
