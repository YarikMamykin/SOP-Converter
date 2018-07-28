#include "Console.h"
//#include "../../logging/Messanger/Messanger.h"


Ui::Console::Console(std::shared_ptr<configuration::ClientManager> cm) :
    QTextEdit(),
    clientManager(cm)
{
    QObject::connect(logging::Logger::getInstance(), SIGNAL(logToConsole(const QString&)), this, SLOT(showLog(const QString&)), Qt::QueuedConnection);
    QObject::connect(clientManager.get(), SIGNAL(clearConsole()), this, SLOT(clear()));
    this->setReadOnly(true);
}
Ui::Console::~Console()
{    
    QObject::disconnect(this,0,0,0);
}
void Ui::Console::showLog(const QString& log)
{
    consoleLocker.lock();
    this->append(log);
    consoleLocker.unlock();
}
