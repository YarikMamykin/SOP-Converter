#include "FoamFile.h"
#include <iostream>

filetypes::FoamFile::FoamFile(const std::string& path, const std::string& fileType, QObject* /*parent*/) :
    header()
  , data(std::make_shared<FoamFileData>())
  , path(path)
  , fileType(fileType)
  , file(path)
  , buffer("")
  , subbuffer("")
  , pair()
{
}

filetypes::FoamFile::~FoamFile()
{
    header.clear();
    data.get()->clear();
    file.close();
}

void filetypes::FoamFile::setHeader(const std::vector<std::pair<std::string, std::string>>&& header)
{
    this->header = std::move(header);
}

void filetypes::FoamFile::setData(std::shared_ptr<FoamFileData> data)
{
    this->data.reset();
    this->data = data;
}

void filetypes::FoamFile::setPath(const std::string&& path)
{
    this->path = std::move(path);
}

std::vector<std::pair<std::string, std::string>>&& filetypes::FoamFile::getHeader(void)
{
    return std::move(this->header);
}

std::shared_ptr<filetypes::FoamFileData> filetypes::FoamFile::getData(void)
{
    return this->data;
}

std::string&& filetypes::FoamFile::getPath(void)
{
    return std::move(this->path);
}

const std::string&& filetypes::FoamFile::getFileType(void)
{
    return std::move(this->fileType);
}

filetypes::FoamFileError filetypes::FoamFile::parseHeader(void)
{
    if(!file.is_open())
    { return FoamFileError::NoFile; }

    while(buffer != std::string("FoamFile")) // shift to header
    { getline(file, buffer); }
    getline(file, buffer); // omit '{'

    // read header
    while(getline(file, buffer) && buffer != std::string("}"))
    {
        std::istringstream splitter(buffer);
        while(getline(splitter, subbuffer, ' '))
        {
            if(subbuffer.length() > 1)
            {
                if(subbuffer[subbuffer.length() - 1] == ';')
                {
                    pair.second = subbuffer.substr(0, subbuffer.length()-1);
                    this->header.push_back(pair);
                }
                else
                { pair.first = subbuffer; }
            }
        }
    }

    // check header
    std::string fileTypeFromHeader = "";
    for(auto& e : this->header)
    {
        if(e.first == "object")
        {
            fileTypeFromHeader = e.second;
            break;
        }
    }

    if(fileTypeFromHeader.empty())
    {
        this->file.close();
        return FoamFileError::CorruptedData;
    }
    else if (fileTypeFromHeader != this->fileType)
    {
        this->file.close();
        return FoamFileError::HeaderMismatch;
    }

    return FoamFileError::NoError;
}
