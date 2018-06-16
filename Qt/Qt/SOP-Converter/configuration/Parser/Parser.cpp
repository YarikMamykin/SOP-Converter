#include "Parser.h"

filemanagment::Parser::Parser() :
    QObject()
{

}

filemanagment::Parser::~Parser()
{

}

filemanagment::Parser* filemanagment::Parser::getInstance()
{
    static Parser instance;
    return &instance;
}
