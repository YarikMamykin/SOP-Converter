#ifndef PARSER_H
#define PARSER_H

#include <QObject>

namespace configuration
{

class Parser : public QObject
{
    Q_OBJECT
public:
    explicit Parser();    
    virtual ~Parser();
};

}

#endif // PARSER_H
