#ifndef PARSER_H
#define PARSER_H

#include <QObject>
#include <memory>
#include <QFile>


namespace configuration
{

class Parser : public QObject
{
    Q_OBJECT
private:
    explicit Parser();
    explicit Parser(const configuration::Parser&) = delete;
    virtual ~Parser();
public:
    static configuration::Parser* getInstance();
    static bool parseIdeasUnvToFoamLog(const QString& result);
    static bool parseTransformPointsLog(const QString& result);
public slots:
    void startParsing();    
private slots:
    bool parseP(std::shared_ptr<QFile> pFile);
    bool parseU(std::shared_ptr<QFile> uFile);
    bool parseBoundary(std::shared_ptr<QFile> bFile);
    bool parseControlDict(std::shared_ptr<QFile> cdFile);
    bool parseTransportProperties(std::shared_ptr<QFile> tpFile);

private:
    bool pParsed;
    bool uParsed;
    bool bParsed;
    bool cdParsed;
    bool tpParsed;
};

}

#endif // PARSER_H
