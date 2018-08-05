#include "Synchronizer.h"
#include "../../configuration/Parser/Parser.h"
#include "../../logging/Logger/Logger.h"
#include "../../configuration/FileManager/FileManager.h"
using Parser = configuration::Parser;
using ParserId = configuration::Parser::ParserId;
using LogManager = logging::Logger;
using FileManager = configuration::FileManager;


const std::vector<std::function<void()>> configuration::Synchronizer::fileSyncRunners
(
{

[]() // p-file syncer
{
    LogManager::getInstance()->log("file syncer p");
    std::shared_ptr<QFile> file =FileManager::getInstance()->getSettingFile("p");
    if(!file.get()->open(QIODevice::ReadOnly|QIODevice::Text))
    {
        file.get()->close();
        throw FileManager::Exception(QString("Can't open file %1").arg(file.get()->fileName()));
    }

    std::shared_ptr<QFile> temp = std::make_shared<QFile>(file.get()->fileName() + QString(".temp"));
    if(!temp.get()->open(QIODevice::WriteOnly|QIODevice::Text))
    {
        temp.get()->close();
        throw FileManager::Exception(QString("Can't open file %1").arg(temp.get()->fileName()));
    }

    QString buffer;
    QTextStream filedata(file.get());
    QTextStream tempdata(temp.get());
    ParserId fileId = Parser::matchParserIdToFile(file);
    do
    {
        buffer = filedata.readLine();
        tempdata << buffer.append('\n');
    }while(!buffer.contains("boundaryField"));
    tempdata << filedata.readLine() << QString("\n"); // writes down '{'

    for(auto e : *Parser::getInstance()->getParserMap(fileId).get())
    {
        Parser::getInstance()->getFormatNodeLocker().get()->lock();
        tempdata << Parser::formatNode(e->first, e->second).c_str();
        Parser::getInstance()->getFormatNodeLocker().get()->unlock();
    }
    tempdata << std::string("}\n").c_str(); // closing bracket for boundaryField

    file.get()->close();
    temp.get()->close();
    file.get()->remove();
    LogManager::getInstance()->log(QString("File synced %1 --> %2").
                                   arg(file.get()->fileName()).
                                   arg(boolToString(temp.get()->rename(file.get()->fileName()))));
},
[]() // U-file syncer
{
    LogManager::getInstance()->log("file syncer U");
    std::shared_ptr<QFile> file =FileManager::getInstance()->getSettingFile("U");
    if(!file.get()->open(QIODevice::ReadOnly|QIODevice::Text))
    {
        file.get()->close();
        throw FileManager::Exception(QString("Can't open file %1").arg(file.get()->fileName()));
    }

    std::shared_ptr<QFile> temp = std::make_shared<QFile>(file.get()->fileName() + QString(".temp"));
    if(!temp.get()->open(QIODevice::WriteOnly|QIODevice::Text))
    {
        temp.get()->close();
        throw FileManager::Exception(QString("Can't open file %1").arg(temp.get()->fileName()));
    }

    QString buffer;
    QTextStream filedata(file.get());
    QTextStream tempdata(temp.get());
    ParserId fileId = Parser::matchParserIdToFile(file);
    do
    {
        buffer = filedata.readLine();
        tempdata << buffer.append('\n');
    }while(!buffer.contains("boundaryField"));
    tempdata << filedata.readLine() << QString("\n"); // writes down '{'

    for(auto e : *Parser::getInstance()->getParserMap(fileId).get())
    {
        Parser::getInstance()->getFormatNodeLocker().get()->lock();
        tempdata << Parser::formatNode(e->first, e->second).c_str();
        Parser::getInstance()->getFormatNodeLocker().get()->unlock();
    }
    tempdata << std::string("}\n").c_str(); // closing bracket for boundaryField

    file.get()->close();
    temp.get()->close();
    file.get()->remove();
    LogManager::getInstance()->log(QString("File synced %1 --> %2").
                                arg(file.get()->fileName()).
                                arg(boolToString(temp.get()->rename(file.get()->fileName()))));
},
[]() // boundary-file syncer
{
    LogManager::getInstance()->log("file syncer boundary");
    std::shared_ptr<QFile> file =FileManager::getInstance()->getSettingFile("boundary");
    if(!file.get()->open(QIODevice::ReadOnly|QIODevice::Text))
    {
        file.get()->close();
        throw FileManager::Exception(QString("Can't open file %1").arg(file.get()->fileName()));
    }

    std::shared_ptr<QFile> temp = std::make_shared<QFile>(file.get()->fileName() + QString(".temp"));
    if(!temp.get()->open(QIODevice::WriteOnly|QIODevice::Text))
    {
        temp.get()->close();
        throw FileManager::Exception(QString("Can't open file %1").arg(temp.get()->fileName()));
    }

    QString buffer;
    QTextStream filedata(file.get());
    QTextStream tempdata(temp.get());

},
[]() // controlDict-file syncer
{
    LogManager::getInstance()->log("file syncer controlDict");
},
[]() // transformProperties-file syncer
{
    LogManager::getInstance()->log("file syncer transportProperties");
}
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
    try
    {
        startRunner();
        emit end(id, true);
    } catch(FileManager::Exception& e)
    {
        emit end(id, false);
    }

    emit finished();
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
