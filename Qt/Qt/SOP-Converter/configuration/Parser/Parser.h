#ifndef PARSER_H
#define PARSER_H

#include <QObject>

namespace filemanagment
{

class Parser : public QObject
{
    Q_OBJECT
private:
    explicit Parser();
    explicit Parser(const Parser&) = delete;
    virtual ~Parser();
public:
    static Parser* getInstance();
};

}

#endif // PARSER_H
