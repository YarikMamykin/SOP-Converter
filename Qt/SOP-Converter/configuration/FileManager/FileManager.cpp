#include "FileManager.h"


configuration::FileManager::FileManager(QWidget* parent) :
    QObject(parent),
    logFile(new QFile),
    backupDir(new QDir("/opt/openfoam211/tutorials/incompressible/icoFoam/cavity")),
    projectFile(new QDomDocument),
    meshFile(std::make_shared<QFile>()),
    workDir(std::make_shared<QDir>())
{
    createLogFile();
    // init vector of files
    for(auto i = 0; i < 4; i++)
    {
        settingFiles.push_back(std::make_shared<QFile>());
    }
}

configuration::FileManager::~FileManager()
{
    logFile->close();
    delete logFile;
    QObject::disconnect(configuration::FileManager::getInstance(),0,0,0);
}

configuration::FileManager* configuration::FileManager::getInstance()
{
    static configuration::FileManager instance;
    return &instance;
}

void configuration::FileManager::logToFile(const QString &log)
{
    if(logFile->open(QIODevice::Append|QIODevice::Text))
    {
        if(!logFile->write((log + QString("\n")).toStdString().c_str()))
            logging::Messanger::getInstance()->showMessage(QString("file write didn't occur"));
        logFile->close();
    } else {logging::Messanger::getInstance()->showMessage(QString("error opening file"));}
}

void configuration::FileManager::createLogFile()
{
    int fileNumber = 0;
    QString filePath("/tmp/LOG");
    do
    {
        logFile->setFileName
                (
                    QString().sprintf("%s%d", filePath.toStdString().c_str(), fileNumber)
                );
        fileNumber++;
    }while(logFile->exists());

    // create file
    if(!logFile->open(QIODevice::Append|QIODevice::Text))
    {
        logging::Messanger::getInstance()->showMessage(QString("Couldn't open log file"));
    }
    logFile->close();
}
