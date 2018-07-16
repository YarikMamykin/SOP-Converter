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
    boundaryMap(std::make_shared<std::map<std::string, std::string>>()),
    uMap(std::make_shared<std::map<std::string, std::string>>())
{    
    QObject::connect(this, SIGNAL(startParsing()), SLOT(ParseAll()), Qt::QueuedConnection);
    QObject::connect(this, SIGNAL(startParseP()), SLOT(parseP()), Qt::QueuedConnection);
    QObject::connect(this, SIGNAL(startParseU()), SLOT(parseU()), Qt::QueuedConnection);
    QObject::connect(this, SIGNAL(startParseBoundary()), SLOT(parseBoundary()), Qt::QueuedConnection);
    QObject::connect(this, SIGNAL(startParseControlDict()), SLOT(parseControlDict()), Qt::QueuedConnection);
    QObject::connect(this, SIGNAL(startParseTransportProperties()), SLOT(parseTransportProperties()), Qt::QueuedConnection);

    resetFlags();

    LogManager::getInstance()->log("Parser constructed", logging::LogDirection::file);
}

configuration::Parser::~Parser()
{    
    boundaryMap.get()->clear();
    uMap.get()->clear();
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
    Parser::parserFlags[static_cast<int>(ParserId::p)] = true;
    LogManager::getInstance()->log("parseP --> " + boolToString(Parser::parserFlags[static_cast<int>(ParserId::p)]));
    collectResults();
}

void configuration::Parser::parseU()
{
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
    bool read_patch_value = false;

    while(!data->readLine().contains("boundaryField")); data->readLine(); // shift to patches
    uMap.get()->clear(); // clear current boundary data

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

            type_value.empty() ? type_value = buffer.toStdString() :
                                 type_value = buffer.toStdString() + std::string(" ") + type_value ; // in case of reverse order of value and type
            type_value = buffer.toStdString();


            read_patch_type = false; continue;
        }
        if(read_patch_value)
        {
            // SEE TODO_LIST.TXT on doc branch about value parsing implementation
            type_value.empty() ? type_value = buffer.toStdString() : // in case of reverse order of value and type
                                 type_value = type_value + std::string(" ") + buffer.toStdString() ;
            read_patch_value = false; continue;
        }
        if(buffer.contains("{"))
        {
            key = prevLine.trimmed().toStdString();
            read_patch_type = true; continue;
        }
        if(buffer.contains("value")) { read_patch_value = true; continue; }
        if(buffer.contains("}")) {uMap.get()->insert(std::pair<std::string, std::string>(key,type_value));}
    }

    Parser::parserFlags[static_cast<int>(ParserId::U)] = true;
    LogManager::getInstance()->log("parseU --> " + boolToString(Parser::parserFlags[static_cast<int>(ParserId::U)]));
    collectResults();

    LogManager::getInstance()->log(QString("Printing uMap (%1)").arg(uMap.get()->size()));
    for(auto e : *uMap.get())
    {
        LogManager::getInstance()->log(QString("Having patch --> ") + QString(e.first.c_str()));
        LogManager::getInstance()->log(QString("Having patch type --> ") + QString(e.second.c_str()));
    }

    file.get()->close();
    delete data;
}

void configuration::Parser::parseBoundary()
{
    std::shared_ptr<QFile> file = FileManager::getInstance()->getSettingFile("boundary");

    if(!file.get()->open(QIODevice::ReadOnly|QIODevice::Text))
    {
        LogManager::getInstance()->log("Could not open boundary file for parsing!");
        Parser::parserFlags[static_cast<int>(ParserId::boundary)] = false;
        return;
    }

    QTextStream* data = new QTextStream(file.get());
    QString buffer;
    QStringList splittedBuffer;
    std::string key;
    std::string value;

    bool read_patch_name = false;
    bool read_patch_type = false;

    while(!data->readLine().contains("// *")); // shift to patches
    boundaryMap.get()->clear(); // clear current boundary data

    while(!data->atEnd())
    {
        buffer = data->readLine();

        if(buffer.contains(")")) break;
        if(buffer.isEmpty()) continue;
        if(read_patch_name)
        {
            key = buffer.trimmed().toStdString();
            read_patch_name = false;
        }
        if(read_patch_type)
        {
            splittedBuffer.clear();
            splittedBuffer = (buffer.trimmed().split(" "));
            splittedBuffer.removeAll(QString(""));
            buffer = splittedBuffer[1];
            value = buffer.toStdString();

            boundaryMap.get()->insert(std::pair<std::string, std::string>(key,value));
            read_patch_type = false;
        }
        if(buffer.contains("{")) { read_patch_type = true; continue ; }
        if(buffer.contains("(") || buffer.contains("}")) { read_patch_name = true; continue; }
    }

    Parser::parserFlags[static_cast<int>(ParserId::boundary)] = true;
    LogManager::getInstance()->log("parseBoundary --> " + boolToString(Parser::parserFlags[static_cast<int>(ParserId::boundary)]));
    collectResults();

    for(auto e : *boundaryMap.get())
    {
        LogManager::getInstance()->log(QString("Having patch --> ") + QString(e.first.c_str()));
        LogManager::getInstance()->log(QString("Having patch type --> ") + QString(e.second.c_str()));
    }

    file.get()->close();
    delete data;
}

void configuration::Parser::parseControlDict()
{


    Parser::parserFlags[static_cast<int>(ParserId::controlDict)] = true;
    LogManager::getInstance()->log("parseControlDict --> " + boolToString(Parser::parserFlags[static_cast<int>(ParserId::controlDict)]));
    collectResults();
}

void configuration::Parser::parseTransportProperties()
{
    Parser::parserFlags[static_cast<int>(ParserId::transportProperties)] = true;
    LogManager::getInstance()->log("parseTransportProperties --> " + boolToString(Parser::parserFlags[static_cast<int>(ParserId::transportProperties)]));
    collectResults();
}

void configuration::Parser::collectResults()
{
    ++counter;
    if(counter == 5) LogManager::getInstance()->log("Results collected"); else return;

    for(auto e : parserFlags)
    {
        LogManager::getInstance()->log(boolToString(e));
    }
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

void configuration::ParserThread::run()
{
    LogManager::getInstance()->log("starting parser thread");
    switch(id)
    {
        case Parser::ParserId::p:                   emit Parser::getInstance()->startParseP(); break;
        case Parser::ParserId::U:                   emit Parser::getInstance()->startParseU(); break;
        case Parser::ParserId::boundary:            emit Parser::getInstance()->startParseBoundary(); break;
        case Parser::ParserId::controlDict:         emit Parser::getInstance()->startParseControlDict(); break;
        case Parser::ParserId::transportProperties: emit Parser::getInstance()->startParseTransportProperties(); break;
    }
}
