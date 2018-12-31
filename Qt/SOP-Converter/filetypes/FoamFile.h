#ifndef FOAMFILE_H
#define FOAMFILE_H

#include <QObject>
#include <map>
#include <vector>
#include <memory>
#include <fstream>
#include <sstream>

namespace filetypes
{
    using FoamFileData = std::vector<std::pair<std::string, std::vector<std::pair<std::string,std::string>>>>;
    using FoamFileDataCell = std::pair<std::string, std::vector<std::pair<std::string,std::string>>>;
    using FoamFileDataNode = std::vector<std::pair<std::string,std::string>>;
    using FoamFileDataNodeCell = std::pair<std::string,std::string>;

    enum class FoamFileError : unsigned char
    {
        NoError = 0,
        NoFile = 1,
        HeaderMismatch = 2,
        CorruptedData = 4
    };

    class FoamFile : public QObject
    {
        Q_OBJECT

    protected:
        explicit FoamFile(const std::string& path, const std::string& fileType = "", QObject* parent=0);
        virtual ~FoamFile();

    public:
        void setHeader(const std::vector<std::pair<std::string, std::string>>&& header);
        void setData(std::shared_ptr<FoamFileData> data);
        void setPath(const std::string&& path);
        std::vector<std::pair<std::string, std::string>>&& getHeader(void);
        std::shared_ptr<FoamFileData> getData(void);
        std::string&& getPath(void);
        const std::string&& getFileType(void);

        FoamFileError parseHeader(void);

    public:
        virtual FoamFileError parse(void) = 0;
        virtual FoamFileError save(void) = 0;

    protected:
        std::vector<std::pair<std::string, std::string>> header;
        std::shared_ptr<FoamFileData> data;
        std::string path;
        const std::string fileType;

        // file Parsing/Saving Utils
        std::fstream file;
        std::string buffer;
        std::string subbuffer;
        std::pair<std::string, std::string> pair;
    };

}

#endif // FOAMFILE_H
