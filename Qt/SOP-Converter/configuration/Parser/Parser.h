#ifndef PARSER_H
#define PARSER_H

#include <QObject>
#include <memory>
#include <QFile>
#include <QThread>
#include <QList>


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

    enum class ParserId
    {
        p, U, boundary, controlDict, transportProperties
    };

signals:
    void startParsing(); // parses all
    void startParseP();
    void startParseU();
    void startParseBoundary();
    void startParseControlDict();
    void startParseTransportProperties();
    void endParsing(QList<bool> &results);
private slots:
    void ParseAll();
    void parseP();
    void parseU();
    void parseBoundary();
    void parseControlDict();
    void parseTransportProperties();
    void collectResults();
private:
    // indicate only that parsing has been completed!
    static bool pParsed;
    static bool uParsed;
    static bool bParsed;
    static bool cdParsed;
    static bool tpParsed;
    static unsigned char counter; // counts parsing operations
};

class ParserThread : public QThread
{
    Q_OBJECT
public:
    explicit ParserThread(Parser::ParserId _id) : QThread(), id(_id) {}
private:

    void run() override;

private:
    Parser::ParserId id;
};

}

#endif // PARSER_H
