#include "FoamFiles.h"
#include <fstream>
#include <sstream>
#include <iostream>

filetypes::FileP::FileP(const std::string& path, QObject* /*parent*/) : FoamFile(path, "p") { }
filetypes::FileU::FileU(const std::string& path, QObject* /*parent*/) : FoamFile(path, "U") { }
filetypes::FileBoundary::FileBoundary(const std::string& path, QObject* /*parent*/) : FoamFile(path, "boundary") { }
filetypes::FileControlDict::FileControlDict(const std::string& path, QObject* /*parent*/) : FoamFile(path, "controlDict") { }
filetypes::FileTransportProperties::FileTransportProperties(const std::string& path, QObject* /*parent*/) : FoamFile(path, "transportProperties") { }

filetypes::FileP::~FileP() { }
filetypes::FileU::~FileU() { }
filetypes::FileBoundary::~FileBoundary() { }
filetypes::FileControlDict::~FileControlDict() { }
filetypes::FileTransportProperties::~FileTransportProperties() { }

filetypes::FoamFileError filetypes::FileP::parse(void)
{
    filetypes::FoamFileError headerParsingError = parseHeader();
    if(headerParsingError != filetypes::FoamFileError::NoError)
    {
        this->file.close();
        return headerParsingError;
    }

    // read main data    
    std::string previous = "";
    while(getline(file, buffer))
    {
        // skip section
        if(buffer.empty()
                || buffer.find("}") != std::string::npos
                || buffer.find("/*") != std::string::npos
                || buffer.find("//") != std::string::npos
                || buffer.find("boundaryField") != std::string::npos)
        { continue; }

        // payload section
        if(buffer.find("dimensions") != std::string::npos)
        { this->dimensions = buffer; continue; }

        if(buffer.find("internalField") != std::string::npos)
        { this->internalField = buffer; continue; }

        if(buffer.find("{") != std::string::npos && !previous.empty())
        {
            while(*previous.begin() == ' ')
            { previous.erase(previous.begin(), previous.begin() + 1); }
            this->data.get()->push_back(FoamFileDataCell(previous, FoamFileDataNode()));
            continue;
        }

        std::istringstream splitter(buffer);
        pair.first = pair.second = "";
        while(getline(splitter, subbuffer, ' '))
        {
            if(subbuffer.length() > 0)
            {
                if(subbuffer[subbuffer.length() - 1] == ';')
                {
                    pair.second.append(std::string(" ") + subbuffer.substr(0, subbuffer.length()-1));
                    (--this->data.get()->end())->second.push_back(pair);
                }
                else
                {
                    if(pair.first.empty())
                    { pair.first = subbuffer; }
                    else
                    {
                        if(pair.second.empty())
                        { pair.second = subbuffer; }
                        else
                        { pair.second.append(std::string(" ") + subbuffer); }
                    }
                }
            }
        }
        previous = buffer;
    }

    this->file.close();
    return FoamFileError::NoError;
}

filetypes::FoamFileError filetypes::FileU::parse(void)
{
    filetypes::FoamFileError headerParsingError = parseHeader();
    if(headerParsingError != filetypes::FoamFileError::NoError)
    {
        this->file.close();
        return headerParsingError;
    }

    // read main data
    std::string previous = "";
    while(getline(file, buffer))
    {
        //skip section
        if(buffer.empty()
                || buffer.find("}") != std::string::npos
                || buffer.find("/*") != std::string::npos
                || buffer.find("//") != std::string::npos
                || buffer.find("boundaryField") != std::string::npos)
        { continue; }

        // payload section
        if(buffer.find("dimensions") != std::string::npos)
        { this->dimensions = buffer; continue; }

        if(buffer.find("internalField") != std::string::npos)
        { this->internalField = buffer; continue; }

        if(buffer.find("{") != std::string::npos && !previous.empty())
        {
            while(*previous.begin() == ' ')
            { previous.erase(previous.begin(), previous.begin() + 1); }
            this->data.get()->push_back(FoamFileDataCell(previous, FoamFileDataNode()));
            continue;
        }

        std::istringstream splitter(buffer);
        pair.first = pair.second = "";
        while(getline(splitter, subbuffer, ' '))
        {
            if(subbuffer.length() > 0)
            {
                if(subbuffer[subbuffer.length() - 1] == ';')
                {
                    pair.second.append(std::string(" ") + subbuffer.substr(0, subbuffer.length()-1));
                    (--this->data.get()->end())->second.push_back(pair);
                }
                else
                {
                    if(pair.first.empty())
                    { pair.first = subbuffer; }
                    else
                    {
                        if(pair.second.empty())
                        { pair.second = subbuffer; }
                        else
                        { pair.second.append(std::string(" ") + subbuffer); }
                    }
                }
            }
        }
        previous = buffer;
    }    

    this->file.close();
    return FoamFileError::NoError;
}

filetypes::FoamFileError filetypes::FileBoundary::parse(void)
{
    filetypes::FoamFileError headerParsingError = parseHeader();
    if(headerParsingError != filetypes::FoamFileError::NoError)
    {
        this->file.close();
        return headerParsingError;
    }

    // read main data
    while(buffer != std::string("(")) { getline(file, buffer); } // shift to data
    std::string previous = "";
    while(getline(file, buffer))
    {
        //skip section
        if(buffer.empty()
                || buffer.find("}") != std::string::npos
                || buffer.find("/*") != std::string::npos
                || buffer.find("//") != std::string::npos
                || buffer.find(")") != std::string::npos
                || buffer.find("boundaryField") != std::string::npos)
        { continue; }

        if(buffer.find("{") != std::string::npos && !previous.empty())
        {
            while(*previous.begin() == ' ')
            { previous.erase(previous.begin(), previous.begin() + 1); }
            this->data.get()->push_back(FoamFileDataCell(previous, FoamFileDataNode()));
            continue;
        }

        std::istringstream splitter(buffer);
        while(getline(splitter, subbuffer, ' '))
        {
            if(subbuffer.length() > 1)
            {
                if(subbuffer[subbuffer.length() - 1] == ';')
                {
                    pair.second = subbuffer.substr(0, subbuffer.length()-1);
                    (--this->data.get()->end())->second.push_back(pair);
                }
                else
                {
                    pair.first = subbuffer;
                }
            }
        }
        previous = buffer;
    }

    this->file.close();
    return FoamFileError::NoError;
}

filetypes::FoamFileError filetypes::FileControlDict::parse(void)
{
    filetypes::FoamFileError headerParsingError = parseHeader();
    if(headerParsingError != filetypes::FoamFileError::NoError)
    {
        this->file.close();
        return headerParsingError;
    }

    // read main data        
    pair.first = pair.second = "";
    this->data.get()->push_back(FoamFileDataCell("controlDictData", FoamFileDataNode()));
    while(getline(file, buffer))
    {
        //skip section
        if(buffer.empty()
                || buffer.find("/*") != std::string::npos
                || buffer.find("//") != std::string::npos)
        { continue; }

        std::istringstream splitter(buffer);
        while(getline(splitter, subbuffer, ' '))
        {
            if(subbuffer.length() > 1)
            {
                if(subbuffer[subbuffer.length() - 1] == ';')
                {
                    pair.second = subbuffer.substr(0, subbuffer.length()-1);                    
                    (--(this->data.get()->end()))->second.push_back(pair);
                }
                else
                {
                    pair.first = subbuffer;
                }
            }
        }        
    }

    this->file.close();
    return FoamFileError::NoError;
}

filetypes::FoamFileError filetypes::FileTransportProperties::parse(void)
{
    filetypes::FoamFileError headerParsingError = parseHeader();
    if(headerParsingError != filetypes::FoamFileError::NoError)
    {
        this->file.close();
        return headerParsingError;
    }

    // read main data
    FoamFileDataNode transportProperties = {
     std::pair<std::string, std::string>("kg", ""),
     std::pair<std::string, std::string>("m", ""),
     std::pair<std::string, std::string>("s", ""),
     std::pair<std::string, std::string>("K", ""),
     std::pair<std::string, std::string>("kgmol", ""),
     std::pair<std::string, std::string>("A", ""),
     std::pair<std::string, std::string>("cd", ""),
     std::pair<std::string, std::string>("value", "")
    };
    this->data.get()->push_back(FoamFileDataCell("nu", transportProperties)); // hardcoded but may change later!

    FoamFileDataNode::iterator tpPointer =  (--(this->data.get()->end()))->second.begin();
    bool startDataRetrieving = false;
    while(getline(file, buffer))
    {
        //skip section
        if(buffer.empty()
                || buffer.find("/*") != std::string::npos
                || buffer.find("//") != std::string::npos)
        { continue; }

        std::istringstream splitter(buffer);
        while(getline(splitter, subbuffer, ' '))
        {
            if(subbuffer.length() > 0)
            {
                if(subbuffer.find("]") != std::string::npos)
                { continue; }
                if(subbuffer.find("[") != std::string::npos)
                { startDataRetrieving = true; continue; }
                if(startDataRetrieving)
                {
                    if(subbuffer[subbuffer.length() - 1] == ';')
                    { tpPointer->second = subbuffer.substr(0, subbuffer.length()-1); }
                    else
                    { tpPointer->second = subbuffer; ++tpPointer; }
                }
            }
        }
    }

    this->file.close();
    return FoamFileError::NoError;
}

filetypes::FoamFileError filetypes::FileP::save(void)
{
    filetypes::FoamFileError headerSaveError = saveHeader();
    if(headerSaveError != filetypes::FoamFileError::NoError)
    {
        this->file.close();
        return headerSaveError;
    }

    this->file << std::endl
               << this->dimensions
               << std::endl << std::endl
               << this->internalField
               << std::endl << std::endl
               << "boundaryField" << std::endl
               << "{" << std::endl;

    for(auto& e : *this->data.get())
    {
        this->file << "    " << e.first << std::endl
                   << "    {" << std::endl;
        for(auto& ee : e.second)
        {
            this->file << "        " << ee.first
                       << "    " << ee.second << ";" << std::endl;
        }
        this->file << "    }" << std::endl << std::endl;
    }

    this->file << "}" << std::endl;
    this->file.close();
    return FoamFileError::NoError;
}

filetypes::FoamFileError filetypes::FileU::save(void)
{
    filetypes::FoamFileError headerSaveError = saveHeader();
    if(headerSaveError != filetypes::FoamFileError::NoError)
    {
        this->file.close();
        return headerSaveError;
    }

    this->file << std::endl
               << this->dimensions
               << std::endl << std::endl
               << this->internalField
               << std::endl << std::endl
               << "boundaryField" << std::endl
               << "{" << std::endl;

    for(auto& e : *this->data.get())
    {
        this->file << "    " << e.first << std::endl
                   << "    {" << std::endl;
        for(auto& ee : e.second)
        {
            this->file << "        " << ee.first
                       << "    " << ee.second << ";" << std::endl;
        }
        this->file << "    }" << std::endl << std::endl;
    }

    this->file << "}" << std::endl;
    this->file.close();
    return FoamFileError::NoError;
}

filetypes::FoamFileError filetypes::FileBoundary::save(void)
{
    filetypes::FoamFileError headerSaveError = saveHeader();
    if(headerSaveError != filetypes::FoamFileError::NoError)
    {
        this->file.close();
        return headerSaveError;
    }

    this->file << std::endl << std::endl
               << std::to_string(this->data.get()->size()) << std::endl
               << "(" << std::endl;

    for(auto& e : *this->data.get())
    {
        this->file << "    " << e.first << std::endl
                   << "    {" << std::endl;
        for(auto& ee : e.second)
        {
            this->file << "        " << ee.first
                       << "    " << ee.second << ";" << std::endl;
        }
        this->file << "    }" << std::endl << std::endl;
    }

    this->file << ")" << std::endl;
    this->file.close();
    return FoamFileError::NoError;
}

filetypes::FoamFileError filetypes::FileControlDict::save(void)
{
    filetypes::FoamFileError headerSaveError = saveHeader();
    if(headerSaveError != filetypes::FoamFileError::NoError)
    {
        this->file.close();
        return headerSaveError;
    }

    for(auto& e : *this->data.get())
    {
        for(auto& ee : e.second)
        {
            this->file << ee.first << "    "
                       << ee.second << ";" << std::endl << std::endl;
        }
    }

    this->file.close();
    return FoamFileError::NoError;
}

filetypes::FoamFileError filetypes::FileTransportProperties::save(void)
{
    filetypes::FoamFileError headerSaveError = saveHeader();
    if(headerSaveError != filetypes::FoamFileError::NoError)
    {
        this->file.close();
        return headerSaveError;
    }

    for(auto& e : *this->data.get())
    {
        this->file << e.first << "        " << e.first << " [ ";
        for(auto& ee : e.second)
        {
            if(ee.first == "value")
            { this->file << "] "; }
            this->file << ee.second << " ";
        }
    }
    this->file << std::endl;
    this->file.close();
    return FoamFileError::NoError;
}
