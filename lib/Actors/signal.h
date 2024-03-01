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
    int signalType;
public:
    explicit Signal(QObject *parent = nullptr, QGraphicsItem* newGraphicItem = nullptr);

    int getState();
    QList<int> getAllowedSignalState() const;
    Actor* getRailActor();

    void setDefaultState();
    void addRailActor(Actor* newRailActor);
    void setState(int newSignState, int newSprite);

    ~Signal();

};

#endif // SIGNAL_H
