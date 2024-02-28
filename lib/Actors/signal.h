#ifndef SIGNAL_H
#define SIGNAL_H

#include "railwayobject.h"
#include <QObject>
#include <QList>
#include "dependencies/Enums/SignalEnum.h"


class LIB_EXPORT Signal : public RailwayObject
{
    Q_OBJECT
protected:
    QList<int> allowedSignalState;
    int signalState;
    Actor* railActor; //can´t hold Rail*
public:
    explicit Signal(QObject *parent = nullptr, QGraphicsItem* newGraphicItem = nullptr);
    void setState(int newSignState, int newSprite);
    int getState();
    QList<int> getAllowedSignalState() const;
    void addRailActor(Actor* newRailActor);
    Actor* getRailActor();
    ~Signal();

};

#endif // SIGNAL_H
