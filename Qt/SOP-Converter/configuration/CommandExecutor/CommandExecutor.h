#ifndef CommandExecutor_H
#define CommandExecutor_H

#include <QObject>
#include <QTextStream>
#include <QProcess>
#include <QThread>
#include <QDir>
#include <QFile>
#include <QStringList>
#include <atomic>
#include <memory>

namespace configuration
{

class CommandExecutor : public QObject
{
public:
    explicit CommandExecutor();
    explicit CommandExecutor(const QStringList& _command, std::shared_ptr<QDir> _wDir, std::shared_ptr<QFile> _lFile = nullptr);
    virtual ~CommandExecutor();

    void setCommand(const QStringList& _command);
    void setDir(std::shared_ptr<QDir> _wDir);
    void setFile(std::shared_ptr<QFile> _lFile);
    void setTimeout(const int& _timeout);

    std::unique_ptr<QString> getOutput();

    void bindProcessWithThread();
    void copyOutputToFile();
    void execute();
    void executeAsync();
private:        
    std::unique_ptr<QStringList> command;
    std::unique_ptr<QString> output;
    std::shared_ptr<QDir> wDir;
    std::shared_ptr<QFile> lFile;
    int timeout;
};

}
#endif // CommandExecutor_H
