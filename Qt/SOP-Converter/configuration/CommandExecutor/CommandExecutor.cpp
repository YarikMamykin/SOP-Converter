#include "CommandExecutor.h"
#include "../../logging/Logger/Logger.h"

using LogManager    = logging::Logger;

configuration::CommandExecutor::CommandExecutor() :
    command(nullptr),
    output(nullptr),
    wDir(nullptr),
    lFile(nullptr),
    timeout(-1)
{
    LogManager::getInstance()->log(QString("CommandExecutor created. Command = NONE"));
}

configuration::CommandExecutor::CommandExecutor(const QStringList& _command, std::shared_ptr<QDir> _wDir, std::shared_ptr<QFile> _lFile) :
    command(new QStringList(_command)),
    output(nullptr),
    wDir(_wDir),
    lFile(_lFile),
    timeout(-1)
{    
    LogManager::getInstance()->log(QString("CommandExecutor created. Dir = %1; Command = %2").
                                   arg(_wDir.get()->path()).
                                   arg(_command.join(" ")));
}

configuration::CommandExecutor::~CommandExecutor()
{        
    command.release();
    output.release();
    LogManager::getInstance()->log(QString("CommandExecutor destroyed"));
}

void configuration::CommandExecutor::setCommand(const QStringList& _command)
{
    this->command.reset(new QStringList(_command));
}

void configuration::CommandExecutor::setDir(std::shared_ptr<QDir> _wDir)
{
    this->wDir = _wDir;
}

void configuration::CommandExecutor::setFile(std::shared_ptr<QFile> _lFile)
{
    lFile = _lFile;
}

void configuration::CommandExecutor::setTimeout(const int& _timeout)
{
    this->timeout = _timeout;
}

std::unique_ptr<QString> configuration::CommandExecutor::getOutput()
{
    return std::move(this->output);
}

void configuration::CommandExecutor::bindProcessWithThread()
{ // In case of executeAsync method only!

}

void configuration::CommandExecutor::copyOutputToFile()
{
    if(lFile.get()->open(QIODevice::WriteOnly | QIODevice::Truncate))
    {
        QTextStream logData(lFile.get());
        for(auto e : *output)
        {
            logData << e;
        }
    }
    lFile.get()->close();
}

void configuration::CommandExecutor::execute()
{
    if(!wDir.get())
    {
        LogManager::getInstance()->log("CommandExecutor: Working directory is not specified!");
        return;
    }
    else
    {
        LogManager::getInstance()->log(QString("CommandExecutor: executing ") + command->join(" "));
    }

    QProcess* process = new QProcess;
    process->reset();
    process->setWorkingDirectory(wDir.get()->path());
    process->setProcessChannelMode(QProcess::MergedChannels);
    process->start(command->join(" "));
    process->waitForFinished(this->timeout);
    output.reset(new QString(process->readAllStandardOutput()));

    if(lFile.get() != nullptr)
    {
        LogManager::getInstance()->log(QString("Copying output to file %1").arg(lFile.get()->fileName()));
        copyOutputToFile();
    }
    delete process;
}

void configuration::CommandExecutor::executeAsync()
{

}
