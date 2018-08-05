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
    maps(),
    formatNodeLocker(std::make_shared<QMutex>())
{    
    QObject::connect(this, SIGNAL(startParsing()), SLOT(ParseAll()), Qt::QueuedConnection);
    QObject::connect(this, SIGNAL(startParseP()), SLOT(parseP()), Qt::QueuedConnection);
    QObject::connect(this, SIGNAL(startParseU()), SLOT(parseU()), Qt::QueuedConnection);
    QObject::connect(this, SIGNAL(startParseBoundary()), SLOT(parseBoundary()), Qt::QueuedConnection);
    QObject::connect(this, SIGNAL(startParseControlDict()), SLOT(parseControlDict()), Qt::QueuedConnection);
    QObject::connect(this, SIGNAL(startParseTransportProperties()), SLOT(parseTransportProperties()), Qt::QueuedConnection);
    QObject::connect(this, SIGNAL(endParsing(bool)), SLOT(parsingEnded(bool)), Qt::QueuedConnection);
    QObject::connect(this, SIGNAL(startSyncFiles()), SLOT(syncFiles()), Qt::QueuedConnection);

    resetFlags();

    for(int i = 0; i < 5; i++) maps.push_back(std::make_shared<std::vector<std::pair<std::string, std::string>*>>());

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

    QObject::disconnect(this, 0,0,0);

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
    emit endParsing(
               Parser::parserFlags[static_cast<int>(ParserId::p)]
            && Parser::parserFlags[static_cast<int>(ParserId::U)]
            && Parser::parserFlags[static_cast<int>(ParserId::boundary)]
            && Parser::parserFlags[static_cast<int>(ParserId::controlDict)]
            && Parser::parserFlags[static_cast<int>(ParserId::transportProperties)]);
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
    if(file.get()->size() == 0)
    {
        LogManager::getInstance()->log("p file is EMPTY! No parsing can be applied!");
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
        if(buffer.contains("}")) {maps[static_cast<int>(ParserId::p)].get()->push_back(new std::pair<std::string, std::string>(key,type_value));}
    }


    Parser::parserFlags[static_cast<int>(ParserId::p)] = true;
    LogManager::getInstance()->log("parse p --> " + boolToString(Parser::parserFlags[static_cast<int>(ParserId::p)]));
    collectResults();

    LogManager::getInstance()->log(QString("Printing p map (%1)").arg(maps[static_cast<int>(ParserId::p)].get()->size()));
    for(auto e : *maps[static_cast<int>(ParserId::p)].get())
    {
        LogManager::getInstance()->log(QString("Having patch --> ") + QString(e->first.c_str()));
        LogManager::getInstance()->log(QString("Having patch type --> ") + QString(e->second.c_str()));
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
    if(file.get()->size() == 0)
    {
        LogManager::getInstance()->log("U file is EMPTY! No parsing can be applied!");
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
        if(buffer.contains("}")) {maps[static_cast<int>(ParserId::U)].get()->push_back(new std::pair<std::string, std::string>(key,type_value));}
    }

    Parser::parserFlags[static_cast<int>(ParserId::U)] = true;
    LogManager::getInstance()->log("parse U --> " + boolToString(Parser::parserFlags[static_cast<int>(ParserId::U)]));
    collectResults();

    LogManager::getInstance()->log(QString("Printing U map (%1)").arg(maps[static_cast<int>(ParserId::U)].get()->size()));
    for(auto e : *maps[static_cast<int>(ParserId::U)].get())
    {
        LogManager::getInstance()->log(QString("Having patch --> ") + QString(e->first.c_str()));
        LogManager::getInstance()->log(QString("Having patch type --> ") + QString(e->second.c_str()));
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
    if(file.get()->size() == 0)
    {
        LogManager::getInstance()->log("Boundary file is EMPTY! No parsing can be applied!");
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
            value = buffer.remove(buffer.indexOf(';'), 1).toStdString();

            maps[static_cast<int>(ParserId::boundary)].get()->push_back(new std::pair<std::string, std::string>(key,value));
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
        LogManager::getInstance()->log(QString("Having patch --> ") + QString(e->first.c_str()));
        LogManager::getInstance()->log(QString("Having patch type --> ") + QString(e->second.c_str()));
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
    if(file.get()->size() == 0)
    {
        LogManager::getInstance()->log("controlDict file is EMPTY! No parsing can be applied!");
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
        maps[static_cast<int>(ParserId::controlDict)].get()->push_back(new std::pair<std::string, std::string>(
                                         splittedBuffer[0].toStdString(),
                                         splittedBuffer[1].toStdString()));
    }

    Parser::parserFlags[static_cast<int>(ParserId::controlDict)] = true;
    LogManager::getInstance()->log("parse controlDict --> " + boolToString(Parser::parserFlags[static_cast<int>(ParserId::controlDict)]));
    collectResults();

    LogManager::getInstance()->log(QString("Printing controlDict map (%1)").arg(maps[static_cast<int>(ParserId::controlDict)].get()->size()));
    for(auto e : *maps[static_cast<int>(ParserId::controlDict)].get())
    {
        LogManager::getInstance()->log(QString("Having config --> ") + QString(e->first.c_str()));
        LogManager::getInstance()->log(QString("Having config value --> ") + QString(e->second.c_str()));
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
    if(file.get()->size() == 0)
    {
        LogManager::getInstance()->log("transportProperties file is EMPTY! No parsing can be applied!");
        Parser::parserFlags[static_cast<int>(ParserId::transportProperties)] = false;
        return;
    }

    QTextStream* data = new QTextStream(file.get());
    QString buffer("");
    QStringList splittedBuffer;

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
            maps[static_cast<int>(ParserId::transportProperties)].get()->push_back(new std::pair<std::string, std::string>(tpDimensions[i++].toStdString(), e.toStdString()));
        }
    }catch(std::exception& ex) {LogManager::getInstance()->log(ex.what());}

    LogManager::getInstance()->log(QString("Printing transportProperties map (%1)").arg(maps[static_cast<int>(ParserId::transportProperties)].get()->size()));
    for(auto e : *maps[static_cast<int>(ParserId::transportProperties)].get())
    {
        LogManager::getInstance()->log(QString("Having config --> ") + QString(e->first.c_str()));
        LogManager::getInstance()->log(QString("Having config value --> ") + QString(e->second.c_str()));
    }

    file.get()->close();
    delete data;

    Parser::parserFlags[static_cast<int>(ParserId::transportProperties)] = true;
    LogManager::getInstance()->log("parseTransportProperties --> " + boolToString(Parser::parserFlags[static_cast<int>(ParserId::transportProperties)]));
    collectResults();

    LogManager::getInstance()->log("---#");
}

void configuration::Parser::parsingEnded(bool parsingResult)
{
    LogManager::getInstance()->log(QString("PARSING ENDED --> ") + boolToString(parsingResult));
    if(!parsingResult)
    {
        LogManager::getInstance()->log("Cannot perform syncing!"); return;
    }

    bool syncResult = true;
    try
    {
        syncFiles();
    }catch(FileManager::Exception& e){LogManager::getInstance()->log(e.what()); syncResult = false;}

    if(syncResult)
        emit notifyAll();
    else
        LogManager::getInstance()->log("Sync failed.");
}

void configuration::Parser::collectResults()
{
    ++counter;
    if(counter == maps.size()) LogManager::getInstance()->log("Results collected"); else return;
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
    if( maps[static_cast<int>(ParserId::boundary)].get()->size() != maps[static_cast<int>(ParserId::p)].get()->size()
            ||
        maps[static_cast<int>(ParserId::boundary)].get()->size() != maps[static_cast<int>(ParserId::U)].get()->size())
    {
        maps[static_cast<int>(ParserId::p)].get()->clear();
        maps[static_cast<int>(ParserId::U)].get()->clear();

        for(auto e : *maps[static_cast<int>(ParserId::boundary)].get())
        {
            maps[static_cast<int>(ParserId::p)].get()->push_back(new std::pair<std::string, std::string>(e->first, defaultNodeType));
            maps[static_cast<int>(ParserId::U)].get()->push_back(new std::pair<std::string, std::string>(e->first, defaultNodeType));
        }
    }

    LogManager::getInstance()->log("Start synchronize");
    syncFile(FileManager::getInstance()->getSettingFile("p"));
    syncFile(FileManager::getInstance()->getSettingFile("U"));
    syncFile(FileManager::getInstance()->getSettingFile("boundary"));
    syncFile(FileManager::getInstance()->getSettingFile("controlDict"));
    syncFile(FileManager::getInstance()->getSettingFile("transportProperties"));
    LogManager::getInstance()->log("End synchronize");
}

void configuration::Parser::syncFile(std::shared_ptr<QFile> file)
{
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

    ParserId fileId = matchParserIdToFile(file);

    switch(fileId)
    {
        case ParserId::p:
        case ParserId::U:
        {
            do
            {
                buffer = filedata.readLine();
                tempdata << buffer.append('\n');
            }while(!buffer.contains("boundaryField"));
            tempdata << filedata.readLine() << QString("\n"); // writes down '{'

            for(auto e : *maps[static_cast<int>(fileId)].get())
            {
                tempdata << formatNode(e->first, e->second).c_str();
            }
            tempdata << std::string("}\n").c_str(); // closing bracket for boundaryField
        }break;
        /* All below parsing needs implementation */
        case ParserId::boundary: file.get()->close(); return; break;
        case ParserId::controlDict: file.get()->close(); return; break;
        case ParserId::transportProperties: file.get()->close(); return; break;
    }

    file.get()->close();
    temp.get()->close();
    file.get()->remove();
    LogManager::getInstance()->log(QString("File synced %1 --> %2").
                                   arg(file.get()->fileName()).
                                   arg(boolToString(temp.get()->rename(file.get()->fileName()))));
}

std::string configuration::Parser::formatNode(const std::string& name, const std::string& type_value)
{
    std::string result = smalltab + name + std::string("\n");
    result.append(smalltab + std::string("{\n"));

    QString buffer(type_value.c_str());
    std::string type("");
    std::string value("");

    if(buffer.contains("fixedValue"))
    {
        type = bigtab + std::string("fixedValue");
        if(buffer.contains("("))
            value.append(buffer.toStdString().substr(buffer.indexOf('('), buffer.indexOf(')') - buffer.indexOf('(') + 1));
        else
            value = buffer.split(" ")[1].toStdString();
    }
    else type = bigtab + type_value;

    result.append(bigtab + std::string("type") + type + std::string(";\n"));
    if(!value.empty())
        result.append(bigtab + std::string("value") + bigtab + std::string("uniform ") + value + std::string(";\n"));
    result.append(smalltab + std::string("}\n"));
    return result;
}

std::shared_ptr<QMutex> configuration::Parser::getFormatNodeLocker()
{ return formatNodeLocker; }

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

std::shared_ptr<std::vector<std::pair<std::string, std::string>*>> configuration::Parser::getParserMap(const ParserId& id)
{
    switch(id)
    {
        case Parser::ParserId::p:                   return maps[static_cast<int>(ParserId::p)]; break;
        case Parser::ParserId::U:                   return maps[static_cast<int>(ParserId::U)]; break;
        case Parser::ParserId::boundary:            return maps[static_cast<int>(ParserId::boundary)]; break;
        case Parser::ParserId::controlDict:         return maps[static_cast<int>(ParserId::controlDict)]; break;
        case Parser::ParserId::transportProperties: return maps[static_cast<int>(ParserId::transportProperties)]; break;
        default:break;
    }
}

QString configuration::Parser::parserIdToString(const ParserId& id)
{
    switch(id)
    {
        case ParserId::p:                   return QString("p"); break;
        case ParserId::U:                   return QString("U"); break;
        case ParserId::boundary:            return QString("boundary"); break;
        case ParserId::controlDict:         return QString("controlDict"); break;
        case ParserId::transportProperties: return QString("transportProperties"); break;
    }
}

ParserId configuration::Parser::matchParserIdToFile(std::shared_ptr<QFile> file)
{
    if(file == configuration::FileManager::getInstance()->getSettingFile("p"))                   return ParserId::p;
    if(file == configuration::FileManager::getInstance()->getSettingFile("U"))                   return ParserId::U;
    if(file == configuration::FileManager::getInstance()->getSettingFile("boundary"))            return ParserId::boundary;
    if(file == configuration::FileManager::getInstance()->getSettingFile("controlDict"))         return ParserId::controlDict;
    if(file == configuration::FileManager::getInstance()->getSettingFile("transportProperties")) return ParserId::transportProperties;
}

std::shared_ptr<QFile> configuration::Parser::matchFileToParserId(ParserId id)
{
    switch(id)
    {
        case ParserId::p:
            return configuration::FileManager::getInstance()->getSettingFile("p");
        break;
        case ParserId::U:
            return configuration::FileManager::getInstance()->getSettingFile("U");
        break;
        case ParserId::boundary:
            return configuration::FileManager::getInstance()->getSettingFile("boundary");
        break;
        case ParserId::controlDict:
            return configuration::FileManager::getInstance()->getSettingFile("controlDict");
        break;
        case ParserId::transportProperties:
            return configuration::FileManager::getInstance()->getSettingFile("transportProperties");
        break;
        default: return nullptr;
    }
}


/* ---------------------------------------------------------------------- */
/* -- ParserThread -- */
/* ---------------------------------------------------------------------- */

configuration::ParserThread::ParserThread(Parser::ParserId _id) :
    QThread(Parser::getInstance()),
    id(_id)
{
    LogManager::getInstance()->log("ParserThread constructed");
}

void configuration::ParserThread::run()
{
    LogManager::getInstance()->log(QString("starting parser thread ") + Parser::parserIdToString(id));
    switch(id)
    {
        case Parser::ParserId::p:                   Parser::getInstance()->parseP(); break;
        case Parser::ParserId::U:                   Parser::getInstance()->parseU(); break;
        case Parser::ParserId::boundary:            Parser::getInstance()->parseBoundary(); break;
        case Parser::ParserId::controlDict:         Parser::getInstance()->parseControlDict(); break;
        case Parser::ParserId::transportProperties: Parser::getInstance()->parseTransportProperties(); break;
    }
}

configuration::ParserThread::~ParserThread()
{
    LogManager::getInstance()->log("ParserThread destroyed");
}

