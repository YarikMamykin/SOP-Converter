#ifndef GENERAL_H
#define GENERAL_H

#include <QString>
#include <QStringList>
#include <string>
#include <QDir>
#include <QFile>
#include <vector>


#include "../configuration/Parser/Parser.h"
using ParserId = configuration::Parser::ParserId;

const QStringList tpDimensions = {"kg","m","s","K","kgmol","A","cd","viscosity"};

// declare here general purpose functions and variables
const std::string defaultNodeType = std::string("empty");
const std::string smalltab        = std::string("    ");
const std::string bigtab          = std::string("        ");

const QString boolToString(const bool& value);
void copyDir(const QDir& from, const QDir& to);
void copyDirRecursively(const QDir& from, const QDir& to);
std::vector<std::pair<std::string, std::string>*>::iterator findKey(const std::string& key,
                                                                    std::vector<std::pair<std::string, std::string>*>& map);


#endif // GENERAL_H
