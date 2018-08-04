#include "Synchronizer.h"
#include "../../logging/Logger/Logger.h"
using LogManager = logging::Logger;


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

