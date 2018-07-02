#include "FileManager.h"
#include <QTextStream>

configuration::FileManager::FileManager(QWidget* parent) :
    QObject(parent),
    maxLogFilesCount(5),
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
    QDir logDir("/tmp");
    QStringList logList = logDir.entryList(QDir::Files);
//    logging::Messanger::getInstance()->showMessage(logList.join("\n"));
    std::vector<QString> logFiles;

    for (auto e : logList)
    {
        if(e.contains("LOG")) logFiles.push_back(e);
        if(logFiles.size() > maxLogFilesCount)
        {
            for(auto i : logFiles)
            {
                QFile::remove(logDir.path() + QString("/") + i);
            }
            logFiles.clear();
        }
    }

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

void configuration::FileManager::setPathToFile(std::shared_ptr<QFile> file, const QString& path)
{
    if (file == meshFile)
    {
        if(!path.contains(".unv", Qt::CaseSensitive))
        {
            QStringList emessage;
            emessage << QString("Wrong file type of:");
            emessage << path;
            throw(configuration::FileManager::Exception(emessage.join(" ")));
        }
    }

    if (file == projectFile)
    {
        if(!path.contains(".xml", Qt::CaseSensitive))
        {
            QStringList emessage;
            emessage << QString("Wrong file type of:");
            emessage << path;
            throw(configuration::FileManager::Exception(emessage.join(" ")));
        }
    }

    file.get()->setFileName(path);
    if(file.get()->exists())
    {
        logging::Logger::getInstance()->log(QString("File selected: ") + file.get()->fileName());
        validatePaths();
    }
    else
    {
        file.get()->setFileName(QString());
        QStringList emessage;
        emessage << QString("No");
        emessage << path;
        emessage << QString("file found");
        throw(configuration::FileManager::Exception(emessage.join(" ")));
    }
}

void configuration::FileManager::setPathToDir(std::shared_ptr<QDir> dir, const QString& path)
{
    dir.get()->setPath(path);
    if(dir.get()->exists())
    {
        logging::Logger::getInstance()->log(QString("Dir selected: ") + dir.get()->path());
        validatePaths();
    }
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
    logging::Logger::getInstance()->log(QString("validating paths..."));
    if(workDir.get()->path().size() != 1) // by default QDir path is set to "."
    {

        QStringList workDirEntryD = workDir.get()->entryList(QDir::Dirs);
        QStringList workDirEntryF = workDir.get()->entryList(QDir::Files);
        logging::Logger::getInstance()->log((workDirEntryD + workDirEntryF).join(" | "), logging::LogDirection::console);
    }
    if(!meshFile.get()->fileName().isEmpty())
    {
        QString rootDir = QFileInfo(meshFile.get()->fileName()).absoluteDir().path();
        logging::Logger::getInstance()->log(meshFile.get()->fileName(), logging::LogDirection::console);
        logging::Logger::getInstance()->log(QString("root dir = ") + rootDir, logging::LogDirection::console);
    }
}
