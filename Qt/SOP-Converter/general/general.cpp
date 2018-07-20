#include "general.h"

const QString boolToString(const bool& value) { return value ? "true" : "false"; }

void copyDir(const QDir& from, const QDir& to)
{
    if(to.path().isEmpty() || from.path().isEmpty()) return;

    to.mkdir(to.path());
    for(auto e : from.entryList(QDir::Files))
    {
        QFile::copy(from.path()+QString("/%1").arg(e), to.path()+QString("/%1").arg(e));
    }
}

void copyDirRecursively(const QDir& from, const QDir& to)
{
    if(to.path().isEmpty() || from.path().isEmpty()) return;
    QStringList direntry = from.entryList(QDir::AllDirs | QDir::NoDotAndDotDot);

    if(direntry.size() == 0)
    {
        copyDir(from, to); return;
    }

    for(auto e : direntry)
    {
        to.mkdir(to.path());
        copyDirRecursively(from.path()+QString("/%1").arg(e), to.path()+QString("/%1").arg(e));
        copyDir(from, to);
    }
}

const QString parserIdToString(const ParserId& id)
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
