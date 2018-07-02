#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <QObject>
#include <QFile>
#include <QFileInfo>
#include <QDir>
#include <QStringList>
#include <exception>
#include <memory>
#include <map>
#include "../../logging/Messanger/Messanger.h"
#include "../../logging/Logger/Logger.h"
#include "../ProjectFile/ProjectFile.h"

namespace configuration
{

class FileManager : public QObject
{
    Q_OBJECT
private:
    explicit FileManager(QWidget* parent = 0);
    virtual ~FileManager();

    void createLogFile();

public:
    static configuration::FileManager* getInstance();
    void setPathToFile(std::shared_ptr<QFile> file, const QString& path);
    void setPathToDir(std::shared_ptr<QDir> dir, const QString& path);

    void validatePaths();

    std::shared_ptr<QFile> getProjectFile();
    std::shared_ptr<QFile> getMeshFile();
    std::shared_ptr<QDir> getWorkDir();
    std::shared_ptr<QFile> getSettingFile(std::string& filename);
    QStringList& getListOfSettingFiles();

    class Exception;
public slots:
    void logToFile(const QString& log);
    void saveProjectFile(const configuration::ProjectFile& pfile);
private:
    unsigned int maxLogFilesCount;
    QFile* logFile;
    QDir* backupDir;
    std::shared_ptr<QFile> projectFile; // XML file for saving project settings
    std::shared_ptr<QFile> meshFile;
    std::shared_ptr<QDir> workDir; // where mesh file is placed
    std::map<std::string, std::shared_ptr<QFile>> settingFiles; // p, U, (T), boundary, controlDict ...
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
