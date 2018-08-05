#include "Synchronizer.h"
#include "../../configuration/Parser/Parser.h"
#include "../../logging/Logger/Logger.h"
using Parser = configuration::Parser;
using LogManager = logging::Logger;


const std::vector<std::function<void()>> configuration::Synchronizer::fileSyncRunners
(
{
    []() // p-file syncer
    {
        LogManager::getInstance()->log("file syncer p");
    },
    []() // U-file syncer
    {
        LogManager::getInstance()->log("file syncer U");
    },
    []() // boundary-file syncer
    {
        LogManager::getInstance()->log("file syncer boundary");
    },
    []() // controlDict-file syncer
    {
        LogManager::getInstance()->log("file syncer controlDict");
    },
    []() // transformProperties-file syncer
    {
        LogManager::getInstance()->log("file syncer transportProperties");
    },
}
);

/* ---------------------------------------------------------------------- */
/* -- Synchronizer -- */
/* ---------------------------------------------------------------------- */

configuration::Synchronizer::Synchronizer(std::function<void()> runner, int _id, QObject* parent) :
    QObject(parent),
    startRunner(runner),
    id(_id)
{
    LogManager::getInstance()->log(QString("Synchronizer constructed. Id = %1").arg(QString::number(id)));
}

configuration::Synchronizer::~Synchronizer()
{
    LogManager::getInstance()->log(QString("Synchronizer deleted. Id = %1").arg(QString::number(id)));
}

void configuration::Synchronizer::execute()
{
    startRunner();
    emit finished();
    emit end(id, true);
    LogManager::getInstance()->log(QString("Execution done. Id = %1").arg(QString::number(id)));
}

void configuration::Synchronizer::executeFileSyncRunner(configuration::Synchronizer::ID id)
{
    configuration::Synchronizer::fileSyncRunners[static_cast<unsigned char>(id)]();
}

std::function<void()> configuration::Synchronizer::getFileSyncRunner(ID id)
{
    return configuration::Synchronizer::fileSyncRunners[static_cast<unsigned char>(id)];
}


/* ---------------------------------------------------------------------- */
/* -- SynchronizerThread -- */
/* ---------------------------------------------------------------------- */

configuration::SynchronizerThread::SynchronizerThread(Synchronizer* _syncer) :
    thread(new QThread),
    syncer(_syncer)
{
    syncer->moveToThread(thread);
    QObject::connect(thread, SIGNAL(started()), syncer, SLOT(execute()));
    QObject::connect(syncer, SIGNAL(finished()), thread, SLOT(quit()));
    QObject::connect(syncer, SIGNAL(finished()), syncer, SLOT(deleteLater()));
    QObject::connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));
    QObject::connect(thread, &QThread::finished, [](){ LogManager::getInstance()->log("Thread finished"); });
    QObject::connect(this, SIGNAL(start()), thread, SLOT(start()));

    LogManager::getInstance()->log("SynchronizerThread constructed");
}

configuration::SynchronizerThread::~SynchronizerThread()
{
    LogManager::getInstance()->log("SynchronizerThread destroyed");
}
