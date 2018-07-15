#include "Parser.h"

#include "../../logging/Logger/Logger.h"
#include "../../configuration/FileManager/FileManager.h"

using LogManager = logging::Logger;
using FileManager = configuration::FileManager;

// static parsing flags
bool configuration::Parser::pParsed = false;
bool configuration::Parser::uParsed = false;
bool configuration::Parser::bParsed = false;
bool configuration::Parser::cdParsed = false;
bool configuration::Parser::tpParsed = false;
unsigned char configuration::Parser::counter = 0;

configuration::Parser::Parser() :
    QObject()
{    
    QObject::connect(this, SIGNAL(startParsing()), SLOT(ParseAll()), Qt::QueuedConnection);
    QObject::connect(this, SIGNAL(startParseP()), SLOT(parseP()), Qt::QueuedConnection);
    QObject::connect(this, SIGNAL(startParseU()), SLOT(parseU()), Qt::QueuedConnection);
    QObject::connect(this, SIGNAL(startParseBoundary()), SLOT(parseBoundary()), Qt::QueuedConnection);
    QObject::connect(this, SIGNAL(startParseControlDict()), SLOT(parseControlDict()), Qt::QueuedConnection);
    QObject::connect(this, SIGNAL(startParseTransportProperties()), SLOT(parseTransportProperties()), Qt::QueuedConnection);

    LogManager::getInstance()->log("Parser constructed", logging::LogDirection::file);
}

configuration::Parser::~Parser()
{    
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
    Parser::pParsed = true;
    LogManager::getInstance()->log("parseP --> " + boolToString(pParsed));
    collectResults();
}

void configuration::Parser::parseU()
{    
    Parser::uParsed = true;
    LogManager::getInstance()->log("parseU --> " + boolToString(uParsed));
    collectResults();
}

void configuration::Parser::parseBoundary()
{    
    Parser::bParsed = true;
    LogManager::getInstance()->log("parseBoundary --> " + boolToString(bParsed));
    collectResults();
}

void configuration::Parser::parseControlDict()
{
    Parser::cdParsed = true;
    LogManager::getInstance()->log("parseControlDict --> " + boolToString(cdParsed));
    collectResults();
}

void configuration::Parser::parseTransportProperties()
{
    Parser::tpParsed = true;
    LogManager::getInstance()->log("parseTransportProperties --> " + boolToString(tpParsed));
    collectResults();
}

void configuration::Parser::collectResults()
{
    QList<bool> results;
    results.append(Parser::pParsed);
    results.append(Parser::uParsed);
    results.append(Parser::bParsed);
    results.append(Parser::cdParsed);
    results.append(Parser::tpParsed);

    LogManager::getInstance()->log("Results collected");
    for(auto e : results)
    {
        LogManager::getInstance()->log(boolToString(e));
    }
    emit endParsing(results);
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
