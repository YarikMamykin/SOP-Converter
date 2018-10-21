#include "FileManager.h"
#include <QTextStream>

using LogManager        = logging::Logger;
using Message           = logging::Messanger;
using Parser            = configuration::Parser;
using CommandExecutor = configuration::CommandExecutor;

management::FileManager::FileManager(QWidget* parent) :
    QObject(parent),
    maxLogFilesCount(5),
    procExecutor(new QProcess),    
    logFile(std::make_shared<QFile>()),
    icoFoamLogFile(std::make_shared<QFile>()),
    ideasUnvToFoamLogFile(std::make_shared<QFile>()),
    transformPointsLogFile(std::make_shared<QFile>()),
    backupDir(std::make_shared<QDir>("/opt/openfoam211/tutorials/incompressible/icoFoam/cavity")),
    zeroFolderEntryValid(new QStringList),
    polyMeshFolderEntryValid(new QStringList),
    systemFolderEntryValid(new QStringList),
    projectFile(std::make_shared<QFile>("/tmp/Test.xml")),
    meshFile(std::make_shared<QFile>()),
    workDir(std::make_shared<QDir>()),
    instanceLocker()
{
    createLogFile();
    // init vector of files
    settingFiles.insert(std::pair<QString, std::shared_ptr<QFile>>(QString("p"), std::make_shared<QFile>()));
    settingFiles.insert(std::pair<QString, std::shared_ptr<QFile>>(QString("U"), std::make_shared<QFile>()));
    settingFiles.insert(std::pair<QString, std::shared_ptr<QFile>>(QString("boundary"), std::make_shared<QFile>()));
    settingFiles.insert(std::pair<QString, std::shared_ptr<QFile>>(QString("controlDict"), std::make_shared<QFile>()));
    settingFiles.insert(std::pair<QString, std::shared_ptr<QFile>>(QString("transportProperties"), std::make_shared<QFile>()));

    *zeroFolderEntryValid     << "p" << "U";
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

management::FileManager::~FileManager()
{
    procExecutor->close();
    delete procExecutor;
    settingFiles.clear();
    QObject::disconnect(getInstance(),0,0,0);
    zeroFolderEntryValid->clear();     delete zeroFolderEntryValid;
    polyMeshFolderEntryValid->clear(); delete polyMeshFolderEntryValid;
    systemFolderEntryValid->clear();   delete systemFolderEntryValid;

    logToFile("FileManager destructed");    
}

management::FileManager* management::FileManager::getInstance()
{    
    static management::FileManager instance;
//    QMutexLocker locker(&instance.instanceLocker);
    return &instance;
}

void management::FileManager::logToFile(const QString &log)
{    
    if(logFile->open(QIODevice::Append|QIODevice::Text))
    {
        if(!logFile.get()->write((log + QString("\n")).toStdString().c_str()))
            logging::Messanger::getInstance()->showMessage(QString("file write didn't occur"));
        logFile.get()->close();
    } else {logging::Messanger::getInstance()->showMessage(QString("error opening file"));}    
}

void management::FileManager::createLogFile()
{
    QDir logDir("/tmp");
    QStringList logList = logDir.entryList(QDir::Files);
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
        logFile.get()->setFileName
                (
                    QString().sprintf("%s%d", filePath.toStdString().c_str(), fileNumber)
                );
        fileNumber++;
    }while(logFile.get()->exists());

    // create file
    if(!logFile.get()->open(QIODevice::Append|QIODevice::Text))
    {
        logging::Messanger::getInstance()->showMessage(QString("Couldn't open log file"));
    }
    logFile.get()->close();
}

bool management::FileManager::loadBackupFiles()
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
    }

    copyDirRecursively(*backupDir.get(), *workDir.get());

    if(validateZeroFolder() && validateConstantBackedUpFolder() && validateSystemFolder())
        return true;
    else
        return false;
}

void management::FileManager::setPathToFile(std::shared_ptr<QFile> file, const QString& path)
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
            throw(management::FileManager::Exception(emessage.join(" ")));
        }
    }

    if (file == projectFile)
    {
        if(!path.contains(".xml", Qt::CaseSensitive))
        {
            QStringList emessage;
            emessage << QString("Wrong file type of:");
            emessage << path;
            throw(management::FileManager::Exception(emessage.join(" ")));
        }
    }

    file.get()->setFileName(path);
    if(file.get()->exists())
    {
        LogManager::getInstance()->log(QString("File selected: ") + file.get()->fileName());
        validatePaths(management::FileManager::ValidatePathsPoint::meshFile);
    }
    else
    {
        file.get()->setFileName(QString());
        QStringList emessage;
        emessage << QString("No");
        emessage << path;
        emessage << QString("file found");
        throw(management::FileManager::Exception(emessage.join(" ")));
    }
}

void management::FileManager::setPathToDir(std::shared_ptr<QDir> dir, const QString& path)
{
    if(dir.get()->path() != path) dir.get()->setPath(path);
    else { LogManager::getInstance()->log(QString("Dir %1 is already selected!").arg(path)); return;}

    if(dir.get()->exists())
    {
        LogManager::getInstance()->log(QString("Dir selected: ") + dir.get()->path());
        validatePaths(management::FileManager::ValidatePathsPoint::workDir);
    }
    else
    {
        QStringList emessage;
        emessage << QString("No");
        emessage << path;
        emessage << QString("directory found");
        throw(management::FileManager::Exception(emessage.join(" ")));
    }
}

std::shared_ptr<QFile> management::FileManager::getLogFile()
{return logFile;}
std::shared_ptr<QFile> management::FileManager::getIcoFoamLogFile()
{return icoFoamLogFile;}
std::shared_ptr<QFile> management::FileManager::getIdeasUnvToFoamLogFile()
{return ideasUnvToFoamLogFile;}
std::shared_ptr<QFile> management::FileManager::getTransformPointsLogFile()
{return transformPointsLogFile;}
std::shared_ptr<QFile> management::FileManager::getProjectFile()
{return projectFile;}
std::shared_ptr<QFile> management::FileManager::getMeshFile()
{return meshFile;}
std::shared_ptr<QDir> management::FileManager::getWorkDir()
{return workDir;}
std::shared_ptr<QDir> management::FileManager::getBackupDir()
{return backupDir;}
std::shared_ptr<QFile> management::FileManager::getSettingFile(const QString& filename)
{return settingFiles.find(filename)->second;}

QStringList management::FileManager::getListOfSettingFiles()
{
    QStringList result;
    for(auto e : settingFiles)
    {
        result << QString(e.first);
    }
    return result;
}

void management::FileManager::saveProjectFile(const configuration::ProjectFile& pfile)
{
    if(projectFile.get()->open(QIODevice::WriteOnly))
    {
        QTextStream(projectFile.get()) << pfile.toString();
        projectFile.get()->close();
    }
}

void management::FileManager::validatePaths(management::FileManager::ValidatePathsPoint point)
{
    LogManager::getInstance()->log(QString("validating paths..."));
    switch(point)
    {
//        if(workDir.get()->path() != QString(".")) // by default QDir path is set to "."
        case management::FileManager::ValidatePathsPoint::workDir:
        {            
            if(workDir.get()->path().isEmpty()) return;
            QStringList workDirEntryD = workDir.get()->entryList(QDir::Dirs);
            QStringList workDirEntryF = workDir.get()->entryList(QStringList("*.unv"));
            LogManager::getInstance()->log((workDirEntryD + workDirEntryF).join(" | "), logging::LogDirection::fileAndConsole);

            if(workDirEntryF.size() == 0)
            {
                // No mesh file in workspace
                meshFile.get()->setFileName("");
                Message::getInstance()->showMessage("No mesh file in workspace is present. Add mesh file before convertion!");
                LogManager::getInstance()->log("Workspace is not selected!");
                return;
            }
            else if(workDirEntryF.size() > 1)
            {                
                QStringList message;
                message << QString("WARNING! Multiple mesh files are present in workspace --> %1 :").arg(workDir.get()->path());
                message << workDirEntryF.join("\n");
                message << QString("Leave only ONE mesh file in workspace or select another directory");
                Message::getInstance()->showMessage(message.join("\n"));
                LogManager::getInstance()->log("Workspace is not selected!");
                workDir.get()->setPath("");
                return;
            }
            else if(workDirEntryF.size() == 1)
            {
                meshFile.get()->setFileName(workDir.get()->path().append("/") + workDirEntryF[0]);
                LogManager::getInstance()->log(QString("Mesh file in workspace --> ") + meshFile.get()->fileName());
            }

            zeroFolderValid = validateZeroFolder();
            constantFolderValid = validateConstantFolder();
            systemFolderValid = validateSystemFolder();
            LogManager::getInstance()->log(QString("Validating zero folder --> ") + boolToString(zeroFolderValid));
            LogManager::getInstance()->log(QString("Validating constant folder --> ") + boolToString(constantFolderValid));
            LogManager::getInstance()->log(QString("Validating system folder --> ") + boolToString(systemFolderValid));            

            if(zeroFolderValid && constantFolderValid && systemFolderValid && !meshFile.get()->fileName().isEmpty())
            {
                icoFoamLogFile.get()->setFileName(workDir.get()->path() + QString("/icoFoam.log"));
                emit Parser::getInstance()->startParsing(); return;
            }
            else if(!meshFile.get()->fileName().isEmpty())
            {
                LogManager::getInstance()->log(QString("Loading backup files --> ") + boolToString(loadBackupFiles()));                
                ideasUnvToFoamLogFile.get()->setFileName(workDir.get()->path() + QString("/ideasUnvToFoam.log"));
                transformPointsLogFile.get()->setFileName(workDir.get()->path() + QString("/transformPoints.log"));

                /* Execute and check ideasUnvToFoam conversion */

                QStringList command;
                command << "ideasUnvToFoam" << QString(QFileInfo(*meshFile.get()).fileName());

                CommandExecutor* executor = new CommandExecutor(command, workDir, ideasUnvToFoamLogFile);
                executor->setTimeout(60000);
                executor->execute();
                bool convertionResult = Parser::parseIdeasUnvToFoamLog(executor->getOutput());
                LogManager::getInstance()->log(QString("Parsing ideasUnvToFoamLog --> ") + boolToString(convertionResult));


                /* Execute and check transformPoints operation */

                command.clear();
                command << "transformPoints" << "-scale" << "\"(0.001 0.001 0.001)\"";

                executor->setCommand(command);
                executor->setFile(transformPointsLogFile);
                executor->execute();
                convertionResult = convertionResult && Parser::parseTransformPointsLog(executor->getOutput());
                LogManager::getInstance()->log(QString("Parsing transformPoints.log --> ") + boolToString(convertionResult));
                command.clear();
                delete executor;

                convertionResult ? validatePaths(management::FileManager::ValidatePathsPoint::workDir) :
                                   LogManager::getInstance()->log("Error in converting files to OpenFOAM format!");
            }
        } break;

        case management::FileManager::ValidatePathsPoint::meshFile:
        {
            QString rootDir = QFileInfo(meshFile.get()->fileName()).absoluteDir().path();
            LogManager::getInstance()->log(meshFile.get()->fileName());
            LogManager::getInstance()->log(QString("root dir = ") + rootDir);

            workDir.get()->setPath(rootDir);
            validatePaths(management::FileManager::ValidatePathsPoint::workDir);
        }break;
    }
}

bool management::FileManager::validateZeroFolder()
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

bool management::FileManager::validateConstantFolder()
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

bool management::FileManager::validateConstantBackedUpFolder()
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

    QStringList validEntry; validEntry << "blockMeshDict" << "boundary";

    for(auto e : validEntry)
    {
        if(!QFile::exists(polyMeshFolder.path() + QString("/") + e)) return false;
        LogManager::getInstance()->log((polyMeshFolder.path() + QString("/") + e) + QString(" exists!"));
    }

    return true;
}

bool management::FileManager::validateSystemFolder()
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
