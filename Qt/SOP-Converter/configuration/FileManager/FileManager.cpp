#include "FileManager.h"
#include <QTextStream>


using LogManager = logging::Logger;
using Message = logging::Messanger;

configuration::FileManager::FileManager(QWidget* parent) :
    QObject(parent),
    maxLogFilesCount(5),
    logFile(new QFile),
    backupDir(new QDir("/opt/openfoam211/tutorials/incompressible/icoFoam/cavity")),
    zeroFolderEntryValid(new QStringList),
//    constantFolderEntryValid(new QStringList),
    polyMeshFolderEntryValid(new QStringList),
    systemFolderEntryValid(new QStringList),
    projectFile(std::make_shared<QFile>("/tmp/Test.xml")),
    meshFile(std::make_shared<QFile>()),
    workDir(std::make_shared<QDir>())
{
    createLogFile();
    // init vector of files
    settingFiles.insert(std::pair<QString, std::shared_ptr<QFile>>(QString("p"), std::make_shared<QFile>()));
    settingFiles.insert(std::pair<QString, std::shared_ptr<QFile>>(QString("U"), std::make_shared<QFile>()));
    settingFiles.insert(std::pair<QString, std::shared_ptr<QFile>>(QString("boundary"), std::make_shared<QFile>()));
    settingFiles.insert(std::pair<QString, std::shared_ptr<QFile>>(QString("controlDict"), std::make_shared<QFile>()));
    settingFiles.insert(std::pair<QString, std::shared_ptr<QFile>>(QString("transportProperties"), std::make_shared<QFile>()));

    *zeroFolderEntryValid     << "p" << "U";
//    *constantFolderEntryValid << "transportProperties" << "polyMesh";
    *polyMeshFolderEntryValid << "blockMeshDict"
                              << "boundary"
                              << "faces"
                              << "neighbour"
                              << "owner"
                              << "points";
    *systemFolderEntryValid   << "controlDict"
                              << "fvSchemes"
                              << "fvSolution";

    logToFile("FileManager constructed");
}

configuration::FileManager::~FileManager()
{
    delete backupDir;
    settingFiles.clear();
    QObject::disconnect(getInstance(),0,0,0);
    zeroFolderEntryValid->clear();     delete zeroFolderEntryValid;
//    constantFolderEntryValid->clear(); delete constantFolderEntryValid;
    polyMeshFolderEntryValid->clear(); delete polyMeshFolderEntryValid;
    systemFolderEntryValid->clear();   delete systemFolderEntryValid;
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

bool configuration::FileManager::loadBackupFiles()
{
    LogManager::getInstance()->log("Loading backup files");
    QStringList setDirs;
    setDirs << QString("/0")
            << QString("/constant")
            << QString("/system");
    QDir tmp;
    for(auto e : setDirs)
    {
        tmp.setPath(workDir.get()->path() + e);
        LogManager::getInstance()->log(QString("removing ") + tmp.path());
        tmp.removeRecursively();

        // need to make implementation of directory copy!!!!
    }
    return true;
}

void configuration::FileManager::setPathToFile(std::shared_ptr<QFile> file, const QString& path)
{
    if(file.get()->fileName() == path)
    { LogManager::getInstance()->log(QString("File %1 is already selected!").arg(path)); return; }

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
        LogManager::getInstance()->log(QString("File selected: ") + file.get()->fileName());
        validatePaths(configuration::FileManager::ValidatePathsPoint::meshFile);
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
    if(dir.get()->path() != path) dir.get()->setPath(path);
    else { LogManager::getInstance()->log(QString("Dir %1 is already selected!").arg(path)); return;}

    if(dir.get()->exists())
    {
        LogManager::getInstance()->log(QString("Dir selected: ") + dir.get()->path());
        validatePaths(configuration::FileManager::ValidatePathsPoint::workDir);
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
std::shared_ptr<QFile> configuration::FileManager::getSettingFile(const QString& filename) {return settingFiles.find(filename)->second;}

QStringList configuration::FileManager::getListOfSettingFiles()
{
    QStringList result;
    for(auto e : settingFiles)
    {
        result << QString(e.first);
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

void configuration::FileManager::validatePaths(configuration::FileManager::ValidatePathsPoint point)
{
    LogManager::getInstance()->log(QString("validating paths..."));
    switch(point)
    {
//        if(workDir.get()->path() != QString(".")) // by default QDir path is set to "."
        case configuration::FileManager::ValidatePathsPoint::workDir:
        {
            QStringList workDirEntryD = workDir.get()->entryList(QDir::Dirs);
            QStringList workDirEntryF = workDir.get()->entryList(QStringList("*.unv"));
            LogManager::getInstance()->log((workDirEntryD + workDirEntryF).join(" | "), logging::LogDirection::console);

            zeroFolderValid = validateZeroFolder();
            constantFolderValid = validateConstantFolder();
            systemFolderValid = validateSystemFolder();
            LogManager::getInstance()->log(QString("Validating zero folder --> ") + boolToString(zeroFolderValid));
            LogManager::getInstance()->log(QString("Validating constant folder --> ") + boolToString(constantFolderValid));
            LogManager::getInstance()->log(QString("Validating system folder --> ") + boolToString(systemFolderValid));

            if(workDirEntryF.size() == 0)
            {
                // No mesh file in workspace
                meshFile.get()->setFileName("");
                Message::getInstance()->showMessage("No mesh file in workspace is present. Add mesh file before convertion!");
                return;
            }
            else if(workDirEntryF.size() > 0)
            {
                // if one or more mesh file --> select first-trapped in entry list
                meshFile.get()->setFileName(workDir.get()->path() + QString("/") + workDirEntryF[0]);
                LogManager::getInstance()->log(QString("Mesh file is - > ") + meshFile.get()->fileName());
            }

            if(zeroFolderValid && constantFolderValid && systemFolderValid && !meshFile.get()->fileName().isEmpty())
            {
                emit parseFiles();
            }
            else
            {
                loadBackupFiles();
            }
        }break;

        case configuration::FileManager::ValidatePathsPoint::meshFile:
        {
            QString rootDir = QFileInfo(meshFile.get()->fileName()).absoluteDir().path();
            LogManager::getInstance()->log(meshFile.get()->fileName(), logging::LogDirection::console);
            LogManager::getInstance()->log(QString("root dir = ") + rootDir, logging::LogDirection::console);

            workDir.get()->setPath(rootDir);
            validatePaths(configuration::FileManager::ValidatePathsPoint::workDir);
        }break;
    }
}

bool configuration::FileManager::validateZeroFolder()
{
    QDir zeroFolder(workDir.get()->path() + QString("/0"));
    if(!zeroFolder.exists()) return false;

    LogManager::getInstance()->log("Zero folder exists!");

    for(auto e : *zeroFolderEntryValid)
    {
        settingFiles.find(e)->second.get()->setFileName(zeroFolder.path() + QString("/") + e);
        LogManager::getInstance()->log(QString("checking file --> ") + settingFiles.find(e)->second.get()->fileName());
        if(!settingFiles.find(e)->second.get()->exists()) return false;
    }

    return true;
}

bool configuration::FileManager::validateConstantFolder()
{
    QDir constantFolder(workDir.get()->path() + QString("/constant"));
    if(!constantFolder.exists()) return false;

    LogManager::getInstance()->log("Constant folder exists!");

    settingFiles.find("transportProperties")->second.get()->setFileName(constantFolder.path() + QString("/transportProperties"));
    if(!settingFiles.find("transportProperties")->second.get()->exists()) return false;

    LogManager::getInstance()->log("transportProperties file exists!");

    QDir polyMeshFolder(constantFolder.path() + QString("/polyMesh"));
    if(!polyMeshFolder.exists()) return false;

    LogManager::getInstance()->log("polyMesh folder exists!");

    for(auto e : *polyMeshFolderEntryValid)
    {
        if(!QFile::exists(polyMeshFolder.path() + QString("/") + e)) return false;
        LogManager::getInstance()->log((polyMeshFolder.path() + QString("/") + e) + QString(" exists!"));
    }

    settingFiles.find("boundary")->second.get()->setFileName(polyMeshFolder.path() + QString("/boundary"));

    return true;
}

bool configuration::FileManager::validateSystemFolder()
{
    QDir systemFolder(workDir.get()->path() + QString("/system"));
    if(!systemFolder.exists()) return false;

    LogManager::getInstance()->log("system folder exists!");

    for(auto e : *systemFolderEntryValid)
    {
        if(!QFile::exists(systemFolder.path() + QString("/") + e)) return false;
        LogManager::getInstance()->log((systemFolder.path() + QString("/") + e) + QString(" exists!"));
    }

    settingFiles.find("controlDict")->second.get()->setFileName(systemFolder.path() + QString("/controlDict"));

    return true;
}
