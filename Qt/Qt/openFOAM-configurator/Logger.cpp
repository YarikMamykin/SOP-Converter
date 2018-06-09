#include <Logger.h>

logging::Logger::Logger() :
    logFile()
{
    int fileNumber = 0;
    QString filePath("/tmp/LOG");
    do
    {
        filePath = QString("%s%d").arg(filePath).arg(fileNumber);
        logFile.setFileName(filePath);
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
