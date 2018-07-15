#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <QObject>
#include <QFile>
#include <QFileInfo>
#include <QDir>
#include <QStringList>
#include <QProcess>
#include <exception>
#include <memory>
#include <map>
#include <cstdlib>
#include "../../logging/Messanger/Messanger.h"
#include "../../logging/Logger/Logger.h"
#include "../ProjectFile/ProjectFile.h"
#include "../../general/general.h"
#include "../../configuration/ClientManager/ClientManager.h"
#include "../../configuration/Parser/Parser.h"

namespace configuration
{

class FileManager : public QObject
{
    Q_OBJECT
private:
    explicit FileManager(QWidget* parent = 0);
    explicit FileManager(const FileManager&) = delete;
    virtual ~FileManager();

    void createLogFile();
    bool loadBackupFiles();
public:
    enum class ValidatePathsPoint
    {
        meshFile, workDir
    };

    class Exception;

    static configuration::FileManager* getInstance();

    void setPathToFile(std::shared_ptr<QFile> file, const QString& path);
    void setPathToDir(std::shared_ptr<QDir> dir, const QString& path);

    void validatePaths(configuration::FileManager::ValidatePathsPoint point);
    bool validateZeroFolder();
    bool validateConstantFolder();
    bool validateConstantBackedUpFolder();
    bool validateSystemFolder();

    std::shared_ptr<QFile> getProjectFile();
    std::shared_ptr<QFile> getMeshFile();
    std::shared_ptr<QDir> getWorkDir();
    std::shared_ptr<QFile> getSettingFile(const QString& filename);
    QStringList getListOfSettingFiles();



public slots:
    void logToFile(const QString& log);
    void saveProjectFile(const configuration::ProjectFile& pfile);
private:    
    unsigned int maxLogFilesCount;
    QProcess* procExecutor;
    QFile* logFile;
    QDir* backupDir;
    QStringList* zeroFolderEntryValid;
    QStringList* polyMeshFolderEntryValid;
    QStringList* systemFolderEntryValid;
    std::shared_ptr<QFile> projectFile; // XML file for saving project settings
    std::shared_ptr<QFile> meshFile;
    std::shared_ptr<QDir> workDir; // where mesh file is placed
    std::map<QString, std::shared_ptr<QFile>> settingFiles; // p, U, (T), boundary, controlDict, transportProperties ...

    bool zeroFolderValid;
    bool constantFolderValid;
    bool systemFolderValid;
};

class FileManager::Exception : public std::exception
{
public:
    explicit Exception(const QString& _message) {message = _message;}
    virtual ~Exception() {}
    virtual const char* what() const throw()
    { return message.toStdString().c_str(); }
private:
    QString message;    
};
}

#endif // FILEMANAGER_H
