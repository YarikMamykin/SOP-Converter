#ifndef PROJECTFILE_H
#define PROJECTFILE_H

#include <QObject>
#include <QFile>
#include <QtXml/QDomDocument>


namespace configuration
{

class ProjectFile : public QDomDocument
{
    // Q_OBJECT <-- adding this causes vtable error
    /* ProjectFile is represented as XML document */
public:
    explicit ProjectFile();
    virtual ~ProjectFile();
    void setFileStructure();
};

}
#endif // PROJECTFILE_H
