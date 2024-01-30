#ifndef SIGNAL_H
#define SIGNAL_H

#include "railwayobject.h"
#include <QObject>
#include <QList>

//BASIC SIGNALIZATIONs
#define SIGNAL_STOP 0
#define SIGNAL_PROCEED 1
#define SIGNAL_CAUTION 2
#define SIGNAL_DOUBLE_CAUTION 3
#define SIGNAL_SHUNT 4
#define SIGNAL_FREE_CAUTION 5
#define SIGNAL_SLOW 6
#define SIGNAL_DANGER 7

//CUSTOM-ADDITIONAL SIGNALIZATIONs
#define SIGNAL_CUSTOM1 8
#define SIGNAL_CUSTOM2 9
#define SIGNAL_CUSTOM3 10
#define SIGNAL_CUSTOM4 11
#define SIGNAL_CUSTOM5 12
#define SIGNAL_CUSTOM6 13
#define SIGNAL_CUSTOM7 14
#define SIGNAL_CUSTOM8 15

class Signal : public RailwayObject
{
    Q_OBJECT
protected:
    QList<int> allowedSignalState;
    int signalState;
public:
    explicit Signal(QObject *parent = nullptr, QGraphicsItem* newGraphicItem = nullptr);
    void setState(int newSignState);
    int getState();
    ~Signal();
};

#endif // SIGNAL_H
