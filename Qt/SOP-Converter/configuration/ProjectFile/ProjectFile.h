#ifndef PROJECTFILE_H
#define PROJECTFILE_H

#include <QObject>
#include <QFile>
#include <QtXml/QDomDocument>
//#include "../../logging/Logger/Logger.h"

namespace configuration
{

class ProjectFile : public QDomDocument
{
    /* ProjectFile is represented as XML document */
public:
    explicit ProjectFile();
    virtual ~ProjectFile();
    void setFileStructure();
};

}
#endif // PROJECTFILE_H
