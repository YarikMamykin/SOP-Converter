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
#include <QMutex>

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
    { p, U, boundary, controlDict, transportProperties };

    static configuration::Parser* getInstance();
    static bool parseIdeasUnvToFoamLog(std::unique_ptr<QString> result);
    static bool parseTransformPointsLog(std::unique_ptr<QString> result);
    std::shared_ptr<std::vector<std::pair<std::string, std::string>*>> getParserMap(const ParserId&);
    static QString parserIdToString(const ParserId& id);
    static ParserId matchParserIdToFile(std::shared_ptr<QFile> file);
    static std::shared_ptr<QFile> matchFileToParserId(ParserId id);
    void syncFile(std::shared_ptr<QFile> file);
    static std::string formatNode(const std::string& name, const std::string& type_value);
    std::shared_ptr<QMutex> getFormatNodeLocker();
    int getMapsCount();
signals:
    void startParsing(); // parses all
    void startParseP();
    void startParseU();
    void startParseBoundary();
    void startParseControlDict();
    void startParseTransportProperties();
    void endParsing(bool);
    void notifyAll(); // connect to any object that will recieve notify message

    void startSyncFiles();
private slots:
    void ParseAll();
    void parseP();
    void parseU();
    void parseBoundary();
    void parseControlDict();
    void parseTransportProperties();
    void parsingEnded(bool result);

    void collectResults();
    void resetFlags();
    void syncFiles();
    bool checkMaps();
private:
    static std::vector<bool> parserFlags; // indicates only that parsing has been completed!
    static unsigned char counter; // counts ended parsing operations
    std::vector<std::shared_ptr<std::vector<std::pair<std::string, std::string>*>>> maps;
    std::shared_ptr<QMutex> formatNodeLocker;

    friend class ParserThread;
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

}

#endif // PARSER_H
