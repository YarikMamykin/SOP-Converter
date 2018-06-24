#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <QObject>
#include <QFile>
#include <QDir>
#include <QtXml/QDomDocument>
#include <memory>
#include <vector>
#include "../../logging/Messanger/Messanger.h"
#include "../../logging/Logger/Logger.h"

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
    void setMeshFilePath(const std::string& path);
public slots:
    void logToFile(const QString& log);
public:
    enum class FileID {P,U,boundary, controlDict};

private:
    QFile* logFile;
    QDir* backupDir;
    QDomDocument* projectFile; // XML file for saving project settings
    std::shared_ptr<QFile> meshFile;
    std::shared_ptr<QDir> workDir; // where mesh file is placed
    std::vector<std::shared_ptr<QFile>> settingFiles; // p, U, (T), boundary, controlDict ...

};

}
#endif // FILEMANAGER_H
