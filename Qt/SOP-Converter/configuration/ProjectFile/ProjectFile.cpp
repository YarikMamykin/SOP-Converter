#include "ProjectFile.h"
#include "../../logging/Logger/Logger.h"

configuration::ProjectFile::ProjectFile() :
    QDomDocument("test_xml")
{
    logging::Logger::getInstance()->log("ProjectFile constructed");
}

configuration::ProjectFile::~ProjectFile()
{
    logging::Logger::getInstance()->log("ProjectFile destructed", logging::LogDirection::file);
}

void configuration::ProjectFile::setFileStructure()
{
    QDomElement e = this->createElement("e1");
    e.setAttribute("attr", "attr_value");
    QDomText et = this->createTextNode("some_node_text");
    e.appendChild(et);
    this->appendChild(e);
}
