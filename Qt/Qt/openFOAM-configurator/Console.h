#ifndef CONSOLE_H
#define CONSOLE_H

#include <QObject>
#include <QTextEdit>

namespace Ui
{

class Console : public QTextEdit // MAKE IT SINGLETON FOR LOGGER!!!
{
    Q_OBJECT

};

}
#endif // CONSOLE_H
