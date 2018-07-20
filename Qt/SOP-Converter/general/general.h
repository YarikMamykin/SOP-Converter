#ifndef GENERAL_H
#define GENERAL_H

#include <QString>
#include <QDir>
#include <QFile>
#include <QStringList>
#include "../configuration/Parser/Parser.h"
using ParserId = configuration::Parser::ParserId;

// declare here general purpose functions

const QString boolToString(const bool& value);
void copyDir(const QDir& from, const QDir& to);
void copyDirRecursively(const QDir& from, const QDir& to);
const QString parserIdToString(const ParserId& id);

#endif // GENERAL_H
