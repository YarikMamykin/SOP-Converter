#ifndef MESSANGER_H
#define MESSANGER_H

#include <QObject>
#include <QMessageBox>
#include <string>

namespace logging
{

class Messanger : public QObject
{
    Q_OBJECT
private:
    explicit Messanger();
    explicit Messanger(const Messanger&) = delete;
    virtual ~Messanger();
public:
    static Messanger* getInstance();
    void showMessage(const QString& message);
private:
    QMessageBox msgBox;
};

}

#endif // MESSANGER_H
