#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <QObject>
#include <QFile>
#include <QDir>
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
public:
    static configuration::FileManager* getInstance();
public slots:
    void logToFile(const QString& log);
private:
    QFile* logFile;
    std::shared_ptr<QFile> meshFile;
    std::shared_ptr<QDir> workDir;
    std::vector<QFile*> settingFiles; // p, U, (T), boundary ...

};

}
#endif // FILEMANAGER_H
