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

class Parser final : public QObject
{
    Q_OBJECT
private:
    explicit Parser();
    explicit Parser(const configuration::Parser&) = delete;
    virtual ~Parser();
public:
    enum class ParserId : unsigned char
    {
        p, U, boundary, controlDict, transportProperties
    };

    class BoundaryNode;

    static configuration::Parser* getInstance();
    static bool parseIdeasUnvToFoamLog(const QString& result);
    static bool parseTransformPointsLog(const QString& result);
    std::shared_ptr<std::map<std::string, std::string>> getParserMap(const ParserId&);
signals:
    void startParsing(); // parses all
    void startParseP();
    void startParseU();
    void startParseBoundary();
    void startParseControlDict();
    void startParseTransportProperties();
    void endParsing();

    void syncFile(std::shared_ptr<QFile> file);
private slots:
    void ParseAll();
    void parseP();
    void parseU();
    void parseBoundary();
    void parseControlDict();
    void parseTransportProperties();

    void collectResults();
    void resetFlags();
    void syncFiles();
    void syncFile(std::shared_ptr<QFile> file);
private:
    static std::vector<bool> parserFlags; // indicate only that parsing has been completed!
    static unsigned char counter; // counts parsing operations
    std::vector<std::shared_ptr<std::map<std::string, std::string>>> maps;
};

class ParserThread : public QThread
{
    Q_OBJECT
public:
    explicit ParserThread(Parser::ParserId _id);
    virtual ~ParserThread();
private:
    void run() override;
private:
    Parser::ParserId id;
};

class Parser::BoundaryNode
{
private:
    explicit BoundaryNode() = default;
public:
    explicit BoundaryNode(const QString& _name, const QString& _type, const QString& _value = QString("")) :
        name(_name), type(_type), value(_value)
    {  }
    virtual ~BoundaryNode(){}
private:
    QString name;
    QString type;
    QString value;
};

}

#endif // PARSER_H
