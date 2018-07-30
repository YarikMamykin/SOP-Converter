#include "OFCommandExecutor.h"
#include "../../logging/Logger/Logger.h"
using LogManager = logging::Logger;

configuration::OFCommandExecutor::OFCommandExecutor() :
    process(new QProcess),
    command(new QStringList),
    wDir(nullptr)
{
    LogManager::getInstance()->log(QString("OFCommandExecutor created. Command = NONE"));
}

configuration::OFCommandExecutor::OFCommandExecutor(const QStringList& _command, std::shared_ptr<QDir> _wDir) :
    process(new QProcess),
    command(new QStringList(_command)),
    wDir(_wDir)
{
    process->setWorkingDirectory(wDir.get()->path());
    LogManager::getInstance()->log(QString("OFCommandExecutor created. Command = ") + _command.join(" "));
}

configuration::OFCommandExecutor::~OFCommandExecutor()
{
    delete process;
    command->clear();
    delete command;
    LogManager::getInstance()->log(QString("OFCommandExecutor destroyed"));
}

QString configuration::OFCommandExecutor::execute()
{
    if(!wDir) return QString("");
    LogManager::getInstance()->log(QString("OFCommandExecutor: executing command = ") + command->join(" "));
    process->reset();
    process->start(command->join(" "));
    process->waitForFinished();
    return process->readAllStandardOutput();
}

void configuration::OFCommandExecutor::setCommand(const QStringList& _command)
{
    if(this->command)
    {
        this->command->clear();
        delete this->command;
    }
    this->command = new QStringList(_command);
}

void configuration::OFCommandExecutor::setDir(std::shared_ptr<QDir> _wDir)
{
    this->wDir = _wDir;
}
