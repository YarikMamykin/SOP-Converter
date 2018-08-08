#include "Synchronizer.h"
#include "../../configuration/Parser/Parser.h"
#include "../../logging/Logger/Logger.h"
#include "../../configuration/FileManager/FileManager.h"
#include "../../configuration/IcoFoamManager/IcoFoamManager.h"
#include <QDebug>

using Parser       = configuration::Parser;
using ParserId     = configuration::Parser::ParserId;
using LogManager   = logging::Logger;
using FileManager  = configuration::FileManager;
using IFoamManager = configuration::IcoFoamManager;



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
    } while(!buffer.contains("boundaryField"));
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
    bool res = temp.get()->rename(file.get()->fileName());
    LogManager::getInstance()->log(QString("File synced %1 --> %2").
                                   arg(file.get()->fileName()).
                                   arg(boolToString(res)));

    IFoamManager::getInstance()->addSyncResult(static_cast<int>(fileId), res);
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
    } while(!buffer.contains("boundaryField"));
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
    bool res = temp.get()->rename(file.get()->fileName());
    LogManager::getInstance()->log(QString("File synced %1 --> %2").
                                arg(file.get()->fileName()).
                                arg(boolToString(res)));
    IFoamManager::getInstance()->addSyncResult(static_cast<int>(fileId), res);
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

    QString buffer, currentPatch;
    std::string currentPatchType;
    QTextStream filedata(file.get());
    QTextStream tempdata(temp.get());
    auto map = Parser::getInstance()->getParserMap(ParserId::boundary);
    auto iterator = map.get()->end();

    do
    {
        buffer = filedata.readLine();
        tempdata << buffer.append('\n');
    } while(!buffer.contains("("));

    do
    {
        buffer = filedata.readLine();
        iterator = findKey(buffer.trimmed().toStdString(), *map.get());
        if(iterator != map.get()->end())
        {
            currentPatch = buffer;
            currentPatchType = (*iterator)->second;
        }
        if(buffer.contains("type"))
        { buffer = QString((bigtab + std::string("type") + bigtab + smalltab + currentPatchType + std::string(";")).c_str()); }

        tempdata << buffer.append('\n');
    } while(!buffer.contains(")"));

    file.get()->close();
    temp.get()->close();
    file.get()->remove();
    bool res = temp.get()->rename(file.get()->fileName());
    LogManager::getInstance()->log(QString("File synced %1 --> %2").
                                 arg(file.get()->fileName()).
                                 arg(boolToString(res)));
    IFoamManager::getInstance()->addSyncResult(static_cast<int>(ParserId::boundary), res);
},
[]() // controlDict-file syncer
{
    LogManager::getInstance()->log("file syncer controlDict");
    std::shared_ptr<QFile> file =FileManager::getInstance()->getSettingFile("controlDict");
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


    unsigned int maxTabSize = 0;
    unsigned int tabSize = 0;
    QString buffer;
    std::string tab = std::string("");
    QTextStream filedata(file.get());
    QTextStream tempdata(temp.get());
    auto map = Parser::getInstance()->getParserMap(ParserId::controlDict);

    for(auto e : *map.get())
    {
        if(maxTabSize < e->first.size())
        {
            maxTabSize = e->first.size();
        }
    }

    do
    {
        buffer = filedata.readLine();
        tempdata << buffer.append('\n');
    } while(!buffer.contains("//"));

    for(auto e : *map.get())
    {
        tab = std::string("");
        tabSize = maxTabSize - e->first.size();
        for(unsigned int i = 0u; i < tabSize; i++)
        {
            tab.append(" ");
        }
        tab.append(smalltab);
        tempdata << QString((e->first + tab + e->second + std::string(";\n\n")).c_str());
    }

    file.get()->close();
    temp.get()->close();
    file.get()->remove();
    bool res = temp.get()->rename(file.get()->fileName());
    LogManager::getInstance()->log(QString("File synced %1 --> %2").
                                  arg(file.get()->fileName()).
                                  arg(boolToString(res)));
    IFoamManager::getInstance()->addSyncResult(static_cast<int>(ParserId::controlDict), res);
},
[]() // transportProperties-file syncer
{
    LogManager::getInstance()->log("file syncer transportProperties");
    std::shared_ptr<QFile> file =FileManager::getInstance()->getSettingFile("transportProperties");
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

    std::string data = std::string("nu") + bigtab + bigtab + std::string("nu [ ");
    QString buffer;
    QTextStream filedata(file.get());
    QTextStream tempdata(temp.get());
    auto map = Parser::getInstance()->getParserMap(ParserId::transportProperties);

    do
    {
        buffer = filedata.readLine();
        tempdata << buffer.append('\n');
    } while(!buffer.contains("//"));

    for(auto e = map.get()->begin(); e != (--map.get()->end()); ++e)
    {
        data.append((*e)->second);
        data.append(std::string(" "));
    }

    data.append(std::string("] "));
    data.append((*(--map.get()->end()))->second);
    data.append(std::string(";\n"));
    tempdata << QString(data.c_str());

    file.get()->close();
    temp.get()->close();
    file.get()->remove();
    bool res = temp.get()->rename(file.get()->fileName());
    LogManager::getInstance()->log(QString("File synced %1 --> %2").
                                  arg(file.get()->fileName()).
                                  arg(boolToString(res)));
    IFoamManager::getInstance()->addSyncResult(static_cast<int>(ParserId::transportProperties), res);
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
    LogManager::getInstance()->log(QString("Synchronizer constructed. Id = %1").arg(id));
}

configuration::Synchronizer::~Synchronizer()
{
    QObject::disconnect(this,0,0,0);
    LogManager::getInstance()->log(QString("Synchronizer deleted. Id = %1").arg(id));
}

void configuration::Synchronizer::execute()
{
    try
    {
        startRunner();        
    } catch(FileManager::Exception& e)
    {
        LogManager::getInstance()->log(e.what());
    }

    emit finished();
    LogManager::getInstance()->log(QString("Execution done. Id = %1").arg(id));
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
    QObject::connect(this, SIGNAL(start()), thread, SLOT(start()), Qt::QueuedConnection);

    LogManager::getInstance()->log("SynchronizerThread constructed");
}

configuration::SynchronizerThread::~SynchronizerThread()
{
    LogManager::getInstance()->log("SynchronizerThread destroyed");
}
