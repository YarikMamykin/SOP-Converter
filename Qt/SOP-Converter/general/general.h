#ifndef GENERAL_H
#define GENERAL_H

#include <QString>
#include <QDir>
#include <QFile>
#include <QStringList>

// declare here general purpose functions

const QString boolToString(const bool& value);
void copyDir(const QDir& from, const QDir& to);
void copyDirRecursively(const QDir& from, const QDir& to);

#endif // GENERAL_H
