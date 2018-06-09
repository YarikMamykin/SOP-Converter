#include <Messanger.h>

logging::Messanger::Messanger() :
    msgBox()
{

//    msgBox.setContentsMargins(0, 0, 100, 5);
    msgBox.resize(300,50);
    msgBox.setWindowTitle(QString("Messanger"));

}

logging::Messanger::~Messanger()
{

}

logging::Messanger* logging::Messanger::getInstance()
{
    static Messanger instance;
    return &instance;
}

void logging::Messanger::showMessage(const QString& message)
{
    msgBox.setText(message);
//    msgBox.show();
    msgBox.exec();
}
