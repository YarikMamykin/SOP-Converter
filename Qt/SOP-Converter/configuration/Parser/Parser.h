#ifndef PARSER_H
#define PARSER_H

#include <QObject>
#include <memory>
#include <map>
#include <vector>
#include <QFile>
#include <QThread>
#include <QList>
#include <QTextStream>


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

    enum class ParserId : unsigned char
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
    void endParsing();
private slots:
    void ParseAll();
    void parseP();
    void parseU();
    void parseBoundary();
    void parseControlDict();
    void parseTransportProperties();
    void collectResults();

    void resetFlags();
private:
    static std::vector<bool> parserFlags; // indicate only that parsing has been completed!
    static unsigned char counter; // counts parsing operations
    std::shared_ptr<std::map<std::string, std::string>> boundaryMap; // map of boundary properties --> will be shared with
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
