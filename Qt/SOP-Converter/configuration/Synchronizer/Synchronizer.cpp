#include "Synchronizer.h"
#include "../../logging/Logger/Logger.h"
using LogManager = logging::Logger;

configuration::Synchronizer::Synchronizer(std::function<void()> _runner, int _id, QObject* parent) :
    QObject(parent),
    runner(_runner),
    id(_id)
{
    LogManager::getInstance()->log(QString("Synchronizer constructed. Id = %1").arg(QString::number(id)));
}

configuration::Synchronizer::~Synchronizer()
{
    LogManager::getInstance()->log(QString("Synchronizer deleted. Id = %1").arg(QString::number(id)));
}

void configuration::Synchronizer::executor()
{
    runner();
    emit finished();
    emit end(id, true);
    LogManager::getInstance()->log(QString("Execution done."));
}
