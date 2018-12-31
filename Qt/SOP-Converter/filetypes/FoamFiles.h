#ifndef FOAMFILES_H
#define FOAMFILES_H

#include "FoamFile.h"

namespace filetypes
{
    class FileP : public FoamFile
    {
    public:
        explicit FileP(const std::string& path, QObject* parent=0);
        virtual ~FileP();

    public:
        virtual FoamFileError parse(void);
        virtual FoamFileError save(void);

    private:
        std::string dimensions;
        std::string internalField;
    };

    class FileU : public FoamFile
    {
    public:
        explicit FileU(const std::string& path, QObject* parent=0);
        virtual ~FileU();

    public:
        virtual FoamFileError parse(void);
        virtual FoamFileError save(void);

    private:
        std::string dimensions;
        std::string internalField;
    };

    class FileBoundary : public FoamFile
    {
    public:
        explicit FileBoundary(const std::string& path, QObject* parent=0);
        virtual ~FileBoundary();

    public:
        virtual FoamFileError parse(void);
        virtual FoamFileError save(void);
    };

    class FileControlDict : public FoamFile
    {
    public:
        explicit FileControlDict(const std::string& path, QObject* parent=0);
        virtual ~FileControlDict();

    public:
        virtual FoamFileError parse(void);
        virtual FoamFileError save(void);
    };

    class FileTransportProperties : public FoamFile
    {
    public:
        explicit FileTransportProperties(const std::string& path, QObject* parent=0);
        virtual ~FileTransportProperties();

    public:
        virtual FoamFileError parse(void);
        virtual FoamFileError save(void);
    };
}

#endif // FOAMFILES_H
