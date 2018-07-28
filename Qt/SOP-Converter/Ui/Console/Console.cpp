#include "Console.h"
//#include "../../logging/Messanger/Messanger.h"


Ui::Console::Console(std::shared_ptr<configuration::ClientManager> cm) :
    QTextEdit(),
    clientManager(cm)
{
    QObject::connect(logging::Logger::getInstance(), SIGNAL(logToConsole(const QString&)), this, SLOT(showLog(const QString&)), Qt::QueuedConnection);
    this->setReadOnly(true);
}
Ui::Console::~Console()
{    
    QObject::disconnect(logging::Logger::getInstance(), SIGNAL(logToConsole(const QString&)), this, SLOT(showLog(const QString&)));
}
void Ui::Console::showLog(const QString& log)
{
    this->append(log);
}
