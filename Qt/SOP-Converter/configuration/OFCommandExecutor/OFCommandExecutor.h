#ifndef OFCOMMANDEXECUTOR_H
#define OFCOMMANDEXECUTOR_H

#include <QObject>
#include <QProcess>
#include <QDir>
#include <memory>

namespace configuration
{

class OFCommandExecutor : public QObject
{
public:
    explicit OFCommandExecutor();
    explicit OFCommandExecutor(const QString& _command, std::shared_ptr<QDir> _wDir);
    virtual ~OFCommandExecutor();

    QString execute();
    void setCommand(const QString& _command);
private:
    QProcess* process;
    QStringList* command;
    std::shared_ptr<QDir> wDir;
};

}
#endif // OFCOMMANDEXECUTOR_H
