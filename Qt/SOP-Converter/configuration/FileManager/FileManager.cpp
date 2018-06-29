#include "FileManager.h"
#include <QTextStream>

configuration::FileManager::FileManager(QWidget* parent) :
    QObject(parent),
    logFile(new QFile),
    backupDir(new QDir("/opt/openfoam211/tutorials/incompressible/icoFoam/cavity")),
    projectFile(std::make_shared<QFile>("/tmp/Test.xml")),
    meshFile(std::make_shared<QFile>()),
    workDir(std::make_shared<QDir>())
{
    createLogFile();
    // init vector of files
    settingFiles.insert(std::pair<std::string, std::shared_ptr<QFile>>(std::string("p"), std::make_shared<QFile>()));
    settingFiles.insert(std::pair<std::string, std::shared_ptr<QFile>>(std::string("U"), std::make_shared<QFile>()));
    settingFiles.insert(std::pair<std::string, std::shared_ptr<QFile>>(std::string("boundary"), std::make_shared<QFile>()));
    settingFiles.insert(std::pair<std::string, std::shared_ptr<QFile>>(std::string("controlDict"), std::make_shared<QFile>()));

    logToFile("FileManager constructed");
}

configuration::FileManager::~FileManager()
{    
    delete backupDir;
    settingFiles.clear();
    QObject::disconnect(getInstance(),0,0,0);
    logToFile("FileManager destructed");
    logFile->close();
    delete logFile;
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

void configuration::FileManager::setMeshFilePath(const QString& path)
{
    meshFile.get()->setFileName(path);
    if(meshFile.get()->exists())
        logging::Logger::getInstance()->log(QString("Mesh file selected: ") + meshFile.get()->fileName());
    else
    {
        QStringList emessage;
        emessage << QString("No");
        emessage << path;
        emessage << QString("file found");
        throw(configuration::FileManager::Exception(emessage.join(" ")));
    }
}

void configuration::FileManager::setWorkDirPath(const QString& path)
{
    workDir.get()->setPath(path);
    if(workDir.get()->exists())
        logging::Logger::getInstance()->log(QString("Workspace selected: ") + workDir.get()->path());
    else
    {
        QStringList emessage;
        emessage << QString("No");
        emessage << path;
        emessage << QString("directory found");
        throw(configuration::FileManager::Exception(emessage.join(" ")));
    }
}

std::shared_ptr<QFile> configuration::FileManager::getProjectFile() {return projectFile;}
std::shared_ptr<QFile> configuration::FileManager::getMeshFile() {return meshFile;}
std::shared_ptr<QDir> configuration::FileManager::getWorkDir() {return workDir;}
std::shared_ptr<QFile> configuration::FileManager::getSettingFile(std::string& filename) {return settingFiles.find(filename)->second;}

QStringList& configuration::FileManager::getListOfSettingFiles()
{
    QStringList result;
    for(auto e : settingFiles)
    {
        result << QString(e.first.c_str());
    }
    return result;
}

void configuration::FileManager::saveProjectFile(const configuration::ProjectFile& pfile)
{
    if(projectFile.get()->open(QIODevice::WriteOnly))
    {
        QTextStream(projectFile.get()) << pfile.toString();
        projectFile.get()->close();
    }
}

void configuration::FileManager::validatePaths()
{
    //        QStringList workDirFiles = workDir.get()->entryList(QDir::Files);
    //        for(auto e : workDirFiles)
    //        {
    //            if
    //        }

    //        logging::Logger::getInstance()->log(QString("Workspace dirs: ") + workDirConsistance.join("\n"));
    //        workDirConsistance = workDir.get()->entryList(QDir::Dirs);
    //        logging::Logger::getInstance()->log(QString("Workspace dirs: ") + workDirConsistance.join("\n"));
}
