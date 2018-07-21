#include "Parser.h"

#include "../../logging/Logger/Logger.h"
#include "../../configuration/FileManager/FileManager.h"

using LogManager = logging::Logger;
using FileManager = configuration::FileManager;

// static parsing flags
std::vector<bool> configuration::Parser::parserFlags(5);
unsigned char configuration::Parser::counter = 0;

configuration::Parser::Parser() :
    QObject(),
    maps()
{    
    QObject::connect(this, SIGNAL(startParsing()), SLOT(ParseAll()), Qt::QueuedConnection);
    QObject::connect(this, SIGNAL(startParseP()), SLOT(parseP()), Qt::QueuedConnection);
    QObject::connect(this, SIGNAL(startParseU()), SLOT(parseU()), Qt::QueuedConnection);
    QObject::connect(this, SIGNAL(startParseBoundary()), SLOT(parseBoundary()), Qt::QueuedConnection);
    QObject::connect(this, SIGNAL(startParseControlDict()), SLOT(parseControlDict()), Qt::QueuedConnection);
    QObject::connect(this, SIGNAL(startParseTransportProperties()), SLOT(parseTransportProperties()), Qt::QueuedConnection);
    QObject::connect(this, SIGNAL(syncFile(std::shared_ptr<QFile>)), SLOT(syncFile(std::shared_ptr<QFile>)), Qt::QueuedConnection);

    resetFlags();

    for(int i = 0; i < 5; i++) maps.push_back(std::make_shared<std::map<std::string, std::string>>());

    LogManager::getInstance()->log("Parser constructed", logging::LogDirection::file);
}

configuration::Parser::~Parser()
{    
    maps[static_cast<int>(ParserId::boundary)].get()->clear();
    maps[static_cast<int>(ParserId::U)].get()->clear();
    maps[static_cast<int>(ParserId::p)].get()->clear();
    maps[static_cast<int>(ParserId::controlDict)].get()->clear();
    maps[static_cast<int>(ParserId::transportProperties)].get()->clear();
    maps.clear();
    LogManager::getInstance()->log("Parser destroyed", logging::LogDirection::file);    
}

configuration::Parser* configuration::Parser::getInstance()
{
    static configuration::Parser instance;
    return &instance;
}

void configuration::Parser::ParseAll()
{
    LogManager::getInstance()->log("Parse all");
    LogManager::getInstance()->log("Parsing START");

    resetFlags();
    QList<configuration::ParserThread*> parserThreads;
    parserThreads.append(new configuration::ParserThread(Parser::ParserId::boundary));
    parserThreads.append(new configuration::ParserThread(Parser::ParserId::p));
    parserThreads.append(new configuration::ParserThread(Parser::ParserId::U));
    parserThreads.append(new configuration::ParserThread(Parser::ParserId::controlDict));
    parserThreads.append(new configuration::ParserThread(Parser::ParserId::transportProperties));

    for(auto e : parserThreads) { e->start(); }

    LogManager::getInstance()->log("Threads started!");

    for(auto e : parserThreads)
    {
        e->wait();
        delete e;
    }

    parserThreads.clear();

    LogManager::getInstance()->log("Threads ended!");
    LogManager::getInstance()->log("Parsing END");
}

void configuration::Parser::parseP()
{
    LogManager::getInstance()->log("#---");
    LogManager::getInstance()->log("Parsing p file");
    std::shared_ptr<QFile> file = FileManager::getInstance()->getSettingFile("p");

    if(!file.get()->open(QIODevice::ReadOnly|QIODevice::Text))
    {
        LogManager::getInstance()->log("Could not open p file for parsing!");
        Parser::parserFlags[static_cast<int>(ParserId::p)] = false;
        return;
    }

    QTextStream* data = new QTextStream(file.get());
    QString buffer("");
    QString prevLine("");
    QStringList splittedBuffer;
    std::string key;
    std::string type_value;

    bool read_patch_type = false;

    while(!data->readLine().contains("boundaryField")); data->readLine(); // shift to patches
    maps[static_cast<int>(ParserId::p)].get()->clear(); // clear current boundary data

    while(!data->atEnd())
    {
        prevLine = buffer;
        buffer = data->readLine();
        if(buffer.contains("}") && buffer.size() == 1) break;
        if(buffer.isEmpty()) continue;
        if(buffer.contains("{"))
        {
            key = prevLine.trimmed().toStdString();
            read_patch_type = true; continue;
        }
        if(read_patch_type)
        {
            splittedBuffer.clear();
            splittedBuffer = buffer.trimmed().split(" ");
            splittedBuffer.removeAll(QString(""));
            buffer = splittedBuffer[1].remove(splittedBuffer[1].size()-1, 1); // remove ';' char
            type_value = buffer.toStdString();
            read_patch_type = false; continue;
        }
        if(buffer.contains("value"))
        {
            splittedBuffer.clear();
            splittedBuffer = buffer.trimmed().split(" ");
            splittedBuffer.removeAll(QString(""));
            buffer = splittedBuffer[splittedBuffer.size()-1].remove(splittedBuffer[splittedBuffer.size()-1].size()-1, 1);

            type_value.append(std::string(" ") + buffer.toStdString());
        }
        if(buffer.contains("}")) {maps[static_cast<int>(ParserId::p)].get()->insert(std::pair<std::string, std::string>(key,type_value));}
    }


    Parser::parserFlags[static_cast<int>(ParserId::p)] = true;
    LogManager::getInstance()->log("parse p --> " + boolToString(Parser::parserFlags[static_cast<int>(ParserId::p)]));
    collectResults();

    LogManager::getInstance()->log(QString("Printing p map (%1)").arg(maps[static_cast<int>(ParserId::p)].get()->size()));
    for(auto e : *maps[static_cast<int>(ParserId::p)].get())
    {
        LogManager::getInstance()->log(QString("Having patch --> ") + QString(e.first.c_str()));
        LogManager::getInstance()->log(QString("Having patch type --> ") + QString(e.second.c_str()));
    }

    file.get()->close();
    delete data;
    LogManager::getInstance()->log("---#");
}

void configuration::Parser::parseU()
{
    LogManager::getInstance()->log("#---");
    LogManager::getInstance()->log("Parsing U file");
    std::shared_ptr<QFile> file = FileManager::getInstance()->getSettingFile("U");

    if(!file.get()->open(QIODevice::ReadOnly|QIODevice::Text))
    {
        LogManager::getInstance()->log("Could not open U file for parsing!");
        Parser::parserFlags[static_cast<int>(ParserId::U)] = false;
        return;
    }

    QTextStream* data = new QTextStream(file.get());
    QString buffer("");
    QString prevLine("");
    QStringList splittedBuffer;
    std::string key;
    std::string type_value;

    bool read_patch_type = false;

    while(!data->readLine().contains("boundaryField")); data->readLine(); // shift to patches
    maps[static_cast<int>(ParserId::U)].get()->clear(); // clear current boundary data

    while(!data->atEnd())
    {
        prevLine = buffer;
        buffer = data->readLine();
        if(buffer.contains("}") && buffer.size() == 1) break;
        if(buffer.isEmpty()) continue;
        if(buffer.contains("{"))
        {
            key = prevLine.trimmed().toStdString();
            read_patch_type = true; continue;
        }
        if(read_patch_type)
        {
            splittedBuffer.clear();
            splittedBuffer = (buffer.trimmed().split(" "));
            splittedBuffer.removeAll(QString(""));
            buffer = splittedBuffer[1].remove(splittedBuffer[1].size()-1, 1); // remove ';' char
            type_value = buffer.toStdString();
            read_patch_type = false; continue;
        }
        if(buffer.contains("value"))
        {
            buffer = buffer.trimmed();
            type_value.append(std::string(" ") +
                              buffer.toStdString().substr(buffer.indexOf('('), buffer.indexOf(')') - buffer.indexOf('(') + 1));
        }
        if(buffer.contains("}")) {maps[static_cast<int>(ParserId::U)].get()->insert(std::pair<std::string, std::string>(key,type_value));}
    }

    Parser::parserFlags[static_cast<int>(ParserId::U)] = true;
    LogManager::getInstance()->log("parse U --> " + boolToString(Parser::parserFlags[static_cast<int>(ParserId::U)]));
    collectResults();

    LogManager::getInstance()->log(QString("Printing U map (%1)").arg(maps[static_cast<int>(ParserId::U)].get()->size()));
    for(auto e : *maps[static_cast<int>(ParserId::U)].get())
    {
        LogManager::getInstance()->log(QString("Having patch --> ") + QString(e.first.c_str()));
        LogManager::getInstance()->log(QString("Having patch type --> ") + QString(e.second.c_str()));
    }

    file.get()->close();
    delete data;
    LogManager::getInstance()->log("---#");
}

void configuration::Parser::parseBoundary()
{
    LogManager::getInstance()->log("#---");
    std::shared_ptr<QFile> file = FileManager::getInstance()->getSettingFile("boundary");

    if(!file.get()->open(QIODevice::ReadOnly|QIODevice::Text))
    {
        LogManager::getInstance()->log("Could not open boundary file for parsing!");
        Parser::parserFlags[static_cast<int>(ParserId::boundary)] = false;
        return;
    }

    QTextStream* data = new QTextStream(file.get());
    QString buffer("");
    QString prevLine("");
    QStringList splittedBuffer;
    std::string key;
    std::string value;

    bool read_patch_type = false;

    while(!data->readLine().contains("// *")); // shift to patches
    maps[static_cast<int>(ParserId::boundary)].get()->clear(); // clear current boundary data

    while(!data->atEnd())
    {
        prevLine = buffer;
        buffer = data->readLine();

        if(buffer.contains(")")) break;
        if(buffer.isEmpty()) continue;
        if(read_patch_type)
        {
            splittedBuffer.clear();
            splittedBuffer = (buffer.trimmed().split(" "));
            splittedBuffer.removeAll(QString(""));
            buffer = splittedBuffer[1];
            value = buffer.toStdString();

            maps[static_cast<int>(ParserId::boundary)].get()->insert(std::pair<std::string, std::string>(key,value));
            read_patch_type = false; continue;
        }
        if(buffer.contains("{"))
        {
            key = prevLine.trimmed().toStdString();
            read_patch_type = true; continue;
        }
    }

    Parser::parserFlags[static_cast<int>(ParserId::boundary)] = true;
    LogManager::getInstance()->log("parse Boundary --> " + boolToString(Parser::parserFlags[static_cast<int>(ParserId::boundary)]));
    collectResults();

    LogManager::getInstance()->log(QString("Printing boundary map (%1)").arg(maps[static_cast<int>(ParserId::boundary)].get()->size()));
    for(auto e : *maps[static_cast<int>(ParserId::boundary)].get())
    {
        LogManager::getInstance()->log(QString("Having patch --> ") + QString(e.first.c_str()));
        LogManager::getInstance()->log(QString("Having patch type --> ") + QString(e.second.c_str()));
    }

    file.get()->close();
    delete data;
    LogManager::getInstance()->log("---#");
}

void configuration::Parser::parseControlDict()
{
    LogManager::getInstance()->log("#---");
    std::shared_ptr<QFile> file = FileManager::getInstance()->getSettingFile("controlDict");

    if(!file.get()->open(QIODevice::ReadOnly|QIODevice::Text))
    {
        LogManager::getInstance()->log("Could not open controlDict file for parsing!");
        Parser::parserFlags[static_cast<int>(ParserId::controlDict)] = false;
        return;
    }

    QTextStream* data = new QTextStream(file.get());
    QString buffer("");
    QStringList splittedBuffer;

    while(!data->readLine().contains("// *")); // shift to config
    maps[static_cast<int>(ParserId::controlDict)].get()->clear(); // clear current boundary data

    while(!data->atEnd())
    {
        buffer = data->readLine();
        if(buffer.contains("//") || buffer.contains("***") || buffer.isEmpty()) continue;
        buffer = buffer.remove(buffer.size()-1, 1); // remove ';' char
        splittedBuffer.clear();
        splittedBuffer = buffer.trimmed().split(" ");
        splittedBuffer.removeAll(QString(""));
        maps[static_cast<int>(ParserId::controlDict)].get()->insert(std::pair<std::string, std::string>(
                                         splittedBuffer[0].toStdString(),
                                         splittedBuffer[1].toStdString()));
    }

    Parser::parserFlags[static_cast<int>(ParserId::controlDict)] = true;
    LogManager::getInstance()->log("parse controlDict --> " + boolToString(Parser::parserFlags[static_cast<int>(ParserId::controlDict)]));
    collectResults();

    LogManager::getInstance()->log(QString("Printing controlDict map (%1)").arg(maps[static_cast<int>(ParserId::controlDict)].get()->size()));
    for(auto e : *maps[static_cast<int>(ParserId::controlDict)].get())
    {
        LogManager::getInstance()->log(QString("Having config --> ") + QString(e.first.c_str()));
        LogManager::getInstance()->log(QString("Having config value --> ") + QString(e.second.c_str()));
    }

    file.get()->close();
    delete data;
    LogManager::getInstance()->log("---#");
}

void configuration::Parser::parseTransportProperties()
{
    LogManager::getInstance()->log("#---");
    // need to acknowledge what is the meaning of nu string in transportProperties files
    std::shared_ptr<QFile> file = FileManager::getInstance()->getSettingFile("transportProperties");

    if(!file.get()->open(QIODevice::ReadOnly|QIODevice::Text))
    {
        LogManager::getInstance()->log("Could not open transportProperties file for parsing!");
        Parser::parserFlags[static_cast<int>(ParserId::transportProperties)] = false;
        return;
    }

    QTextStream* data = new QTextStream(file.get());
    QString buffer("");
    QStringList splittedBuffer;
    QStringList keys;
    keys << "kg"
         << "m"
         << "s"
         << "K"
         << "kgmol"
         << "A"
         << "cd"
         << "viscosity";

    LogManager::getInstance()->log(QString("Clearing ") + parserIdToString(ParserId::transportProperties));
    maps[static_cast<int>(ParserId::transportProperties)].get()->clear();

    while(!(buffer=data->readLine()).contains("nu")); // shift to config
    buffer = QString(buffer.toStdString().substr(buffer.indexOf('['), buffer.indexOf(';') - buffer.indexOf('[')).c_str());
    LogManager::getInstance()->log(QString("TP BUFFER = %1").arg(buffer));
    splittedBuffer = buffer.split(" ");
    splittedBuffer.removeAll(QString(""));
    splittedBuffer.removeAll(QString("["));
    splittedBuffer.removeAll(QString("]"));

    try
    {
        int i = 0;
        for(auto e : splittedBuffer)
        {
            maps[static_cast<int>(ParserId::transportProperties)].get()->insert(std::pair<std::string, std::string>(keys[i++].toStdString(), e.toStdString()));
        }
    }catch(std::exception& ex) {LogManager::getInstance()->log(ex.what());}

    LogManager::getInstance()->log(QString("Printing transportProperties map (%1)").arg(maps[static_cast<int>(ParserId::transportProperties)].get()->size()));
    for(auto e : *maps[static_cast<int>(ParserId::transportProperties)].get())
    {
        LogManager::getInstance()->log(QString("Having config --> ") + QString(e.first.c_str()));
        LogManager::getInstance()->log(QString("Having config value --> ") + QString(e.second.c_str()));
    }

    file.get()->close();
    delete data;

    Parser::parserFlags[static_cast<int>(ParserId::transportProperties)] = true;
    LogManager::getInstance()->log("parseTransportProperties --> " + boolToString(Parser::parserFlags[static_cast<int>(ParserId::transportProperties)]));
    collectResults();

    LogManager::getInstance()->log("---#");
}

void configuration::Parser::collectResults()
{
    ++counter;
    if(counter == maps.size()) LogManager::getInstance()->log("Results collected"); else return;

    try
    {
        syncFiles();
    }catch(FileManager::Exception& e){LogManager::getInstance()->log(e.what());}

    emit endParsing();
}

void configuration::Parser::resetFlags()
{
    counter = 0;
    for(auto e : parserFlags)
    {
        e = false;
    }
    LogManager::getInstance()->log("Flags reseted");
}

void configuration::Parser::syncFiles()
{
    if( maps[static_cast<int>(ParserId::boundary)].get()->size() == maps[static_cast<int>(ParserId::p)].get()->size()
            &&
        maps[static_cast<int>(ParserId::boundary)].get()->size() == maps[static_cast<int>(ParserId::U)].get()->size())
    { return; }

    maps[static_cast<int>(ParserId::p)].get()->clear();
    maps[static_cast<int>(ParserId::U)].get()->clear();

    std::shared_ptr<QFile> pFile = FileManager::getInstance()->getSettingFile("p");
    std::shared_ptr<QFile> pTemp = std::make_shared<QFile>(pFile.get()->fileName() + QString(".temp"));
    std::shared_ptr<QFile> uFile = FileManager::getInstance()->getSettingFile("U");
    std::shared_ptr<QFile> uTemp = std::make_shared<QFile>(uFile.get()->fileName() + QString(".temp"));

    if(!pFile.get()->open(QIODevice::ReadOnly|QIODevice::Text)) throw FileManager::Exception(QString("Can't open file %1").arg(pFile.get()->fileName()));
    if(!pTemp.get()->open(QIODevice::WriteOnly|QIODevice::Text)) throw FileManager::Exception(QString("Can't open file %1").arg(pTemp.get()->fileName()));
    if(!uFile.get()->open(QIODevice::ReadOnly|QIODevice::Text)) throw FileManager::Exception(QString("Can't open file %1").arg(uFile.get()->fileName()));
    if(!uTemp.get()->open(QIODevice::WriteOnly|QIODevice::Text)) throw FileManager::Exception(QString("Can't open file %1").arg(uTemp.get()->fileName()));

    for(auto e : *maps[static_cast<int>(ParserId::boundary)].get())
    {
        maps[static_cast<int>(ParserId::p)].get()->insert(std::pair<std::string, std::string>(e.first, defaultNodeType));
        maps[static_cast<int>(ParserId::U)].get()->insert(std::pair<std::string, std::string>(e.first, defaultNodeType));
    }

    for(auto e : *maps[static_cast<int>(ParserId::U)].get()) LogManager::getInstance()->log(QString("U pair %1=%2").arg(e.first.c_str()).arg(e.second.c_str()));
    for(auto e : *maps[static_cast<int>(ParserId::p)].get()) LogManager::getInstance()->log(QString("p pair %1=%2").arg(e.first.c_str()).arg(e.second.c_str()));

    // SEE TODO LIST ABOUT IMPLEMENTATION
//    QTextStream pData(pFile.get());
//    QTextStream uData(uFile.get());
//    QTextStream pTempData(pTemp.get());
//    QTextStream uTempData(uTemp.get());
//    emit syncFile(pFile);
//    emit syncFile(uFile);


//    QString buffer;
//    pTemp.get()->write()
    pFile.get()->close();
    pTemp.get()->close();
    uFile.get()->close();
    uTemp.get()->close();
}

bool configuration::Parser::parseIdeasUnvToFoamLog(const QString& result)
{
    QStringList iufres = result.split("\n");
    iufres.removeAll(QString(""));
    if(iufres[iufres.size() - 1] != QString("End"))
        return false;
    else
        return true;
}

bool configuration::Parser::parseTransformPointsLog(const QString& result)
{
    QStringList tplres = result.split("\n");
    tplres.removeAll(QString(""));
    if(tplres[tplres.size() - 1] != QString("Writing points into directory \"%1\"").arg(FileManager::getInstance()->getWorkDir().get()->path()+QString("/constant/polyMesh")))
        return false;
    else
        return true;
}

std::shared_ptr<std::map<std::string, std::string>> configuration::Parser::getParserMap(const ParserId& id)
{
    switch(id)
    {
        case Parser::ParserId::p:                   return maps[static_cast<int>(ParserId::p)]; break;
        case Parser::ParserId::U:                   return maps[static_cast<int>(ParserId::U)]; break;
        case Parser::ParserId::boundary:            return maps[static_cast<int>(ParserId::boundary)]; break;
        case Parser::ParserId::controlDict:         return maps[static_cast<int>(ParserId::controlDict)]; break;
        case Parser::ParserId::transportProperties: return maps[static_cast<int>(ParserId::transportProperties)]; break;
    }
}


configuration::ParserThread::ParserThread(Parser::ParserId _id) :
    QThread(),
    id(_id)
{
    LogManager::getInstance()->log("ParserThread constructed");
}

void configuration::ParserThread::run()
{
    LogManager::getInstance()->log(QString("starting parser thread ") + parserIdToString(id));
    switch(id)
    {
        case Parser::ParserId::p:                   emit Parser::getInstance()->startParseP(); break;
        case Parser::ParserId::U:                   emit Parser::getInstance()->startParseU(); break;
        case Parser::ParserId::boundary:            emit Parser::getInstance()->startParseBoundary(); break;
        case Parser::ParserId::controlDict:         emit Parser::getInstance()->startParseControlDict(); break;
        case Parser::ParserId::transportProperties: emit Parser::getInstance()->startParseTransportProperties(); break;
    }
}

configuration::ParserThread::~ParserThread()
{
    LogManager::getInstance()->log("ParserThread destroyed");
}

