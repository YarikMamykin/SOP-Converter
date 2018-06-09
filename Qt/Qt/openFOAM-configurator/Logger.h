#ifndef LOGGER_H
#define LOGGER_H

#include <QObject>
#include <QFile>
#include <string>

namespace logging
{

class Logger : public QObject
{
    Q_OBJECT
private:
    explicit Logger();
    explicit Logger(const Logger&) = delete;
    virtual ~Logger();
public:
    static Logger* getInstance();
    bool log(const std::string& message);
private:
    QFile logFile;
};

}
#endif // LOGGER_H

