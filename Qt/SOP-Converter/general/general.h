#ifndef GENERAL_H
#define GENERAL_H

#include <QString>
#include <string>
#include <QDir>
#include <QFile>
#include <QStringList>
#include "../configuration/Parser/Parser.h"
using ParserId = configuration::Parser::ParserId;



// declare here general purpose functions and variables
const std::string defaultNodeType = std::string("empty");
const std::string smalltab        = std::string("    ");
const std::string bigtab          = std::string("        ");

const QString boolToString(const bool& value);
void copyDir(const QDir& from, const QDir& to);
void copyDirRecursively(const QDir& from, const QDir& to);


#endif // GENERAL_H
