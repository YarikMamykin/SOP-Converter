#include "Console.h"
#include "Messanger.h"
#include "Logger.h"

Ui::Console::Console() : QTextEdit()
{
    QObject::connect(logging::Logger::getInstance(), SIGNAL(logToConsole(const QString&)), this, SLOT(showLog(const QString&)));
}
Ui::Console::~Console()
{
    QObject::disconnect(logging::Logger::getInstance(), SIGNAL(logToConsole(const QString&)), this, SLOT(showLog(const QString&)));
}
void Ui::Console::showLog(const QString& log)
{
    this->append(log);
}
