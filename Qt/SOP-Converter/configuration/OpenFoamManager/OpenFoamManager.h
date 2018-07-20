#ifndef OPENFOAMMANAGER_H
#define OPENFOAMMANAGER_H

#include <QObject>
#include "../FileManager/FileManager.h"

class OpenFoamManager : public QObject
{
    Q_OBJECT
private:
    explicit OpenFoamManager(QWidget* parent = 0);
    explicit OpenFoamManager(const OpenFoamManager&) = delete;
    virtual ~OpenFoamManager();
public:
    static OpenFoamManager* getInstance();
private slots:
    syncFiles();
};

#endif // OPENFOAMMANAGER_H
