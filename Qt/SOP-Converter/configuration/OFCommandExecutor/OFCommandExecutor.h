#ifndef OFCOMMANDEXECUTOR_H
#define OFCOMMANDEXECUTOR_H

#include <QObject>
#include <QProcess>
#include <QDir>
#include <QStringList>
#include <memory>

namespace configuration
{

class OFCommandExecutor : public QObject
{
public:
    explicit OFCommandExecutor();
    explicit OFCommandExecutor(const QStringList& _command, std::shared_ptr<QDir> _wDir);
    virtual ~OFCommandExecutor();

    QString execute();
    void setCommand(const QStringList& _command);
    void setDir(std::shared_ptr<QDir> _wDir);
private:
    QProcess* process;
    QStringList* command;
    std::shared_ptr<QDir> wDir;
};

}
#endif // OFCOMMANDEXECUTOR_H
