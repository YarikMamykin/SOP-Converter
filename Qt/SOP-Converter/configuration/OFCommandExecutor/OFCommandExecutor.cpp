#include "OFCommandExecutor.h"
#include "../../logging/Logger/Logger.h"
#include "../../management/IcoFoamManager/IcoFoamManager.h"
using LogManager = logging::Logger;
using IcoFoam    = management::IcoFoamManager;

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

void configuration::OFCommandExecutor::executeToFile()
{
    process->setWorkingDirectory(wDir.get()->path());
    process->setReadChannelMode(QProcess::MergedChannels);
    process->setStandardOutputFile(FileManager::getInstance()->getIcoFoamLogFile().get()->fileName());

    process->reset();
    process->terminate();
    process->start(command->join(" "));
    process->setTextModeEnabled(true);
    process->waitForStarted();
    process->waitForReadyRead();

    LogManager::getInstance()->log(QString("icoFoam process STARTED at %1").arg(wDir.get()->path()));

//    process->waitForFinished();

    emit IcoFoam::getInstance()->processStandartOut();
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

void configuration::OFCommandExecutor::terminateProcess()
{
    process->terminate();
}
