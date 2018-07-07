#include "Parser.h"

#include "../../logging/Logger/Logger.h"
#include "../../configuration/FileManager/FileManager.h"

using LogManager = logging::Logger;
using FileManager = configuration::FileManager;

configuration::Parser::Parser() :
    QObject()
{    
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

void configuration::Parser::startParsing()
{
    LogManager::getInstance()->log("Parsing START");
    bParsed = parseBoundary(FileManager::getInstance()->getSettingFile("boundary"));
    pParsed = parseBoundary(FileManager::getInstance()->getSettingFile("p"));
    uParsed = parseBoundary(FileManager::getInstance()->getSettingFile("U"));
    cdParsed = parseBoundary(FileManager::getInstance()->getSettingFile("controlDict"));
    tpParsed = parseBoundary(FileManager::getInstance()->getSettingFile("transportProperties"));
    LogManager::getInstance()->log(QString("Parsing boundary file --> ") + boolToString(bParsed));
    LogManager::getInstance()->log(QString("Parsing p file --> ") + boolToString(pParsed));
    LogManager::getInstance()->log(QString("Parsing U file --> ") + boolToString(uParsed));
    LogManager::getInstance()->log(QString("Parsing controlDict file --> ") + boolToString(cdParsed));
    LogManager::getInstance()->log(QString("Parsing transportProperties file --> ") + boolToString(tpParsed));
    LogManager::getInstance()->log("Parsing END");
}

bool configuration::Parser::parseP(std::shared_ptr<QFile> pFile)
{
    return true;
}

bool configuration::Parser::parseU(std::shared_ptr<QFile> uFile)
{
    return true;
}

bool configuration::Parser::parseBoundary(std::shared_ptr<QFile> bFile)
{
    return true;
}

bool configuration::Parser::parseControlDict(std::shared_ptr<QFile> cdFile)
{
    return true;
}

bool configuration::Parser::parseTransportProperties(std::shared_ptr<QFile> tpFile)
{
    return true;
}
