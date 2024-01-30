#ifndef MANAGERCONSOLE_H
#define MANAGERCONSOLE_H

#include "managerconsolelogic.h"
#include <QObject>

class ManagerConsole : public ManagerConsoleLogic
{
    Q_OBJECT
public:
    explicit ManagerConsole(QObject *parent = nullptr);
    void printToConsole(QString text, int color, int timeToHidden);
    ~ManagerConsole();
};

#endif // MANAGERCONSOLE_H
