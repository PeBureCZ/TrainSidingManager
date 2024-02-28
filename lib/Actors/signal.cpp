#include "signal.h"

Signal::Signal(QObject *parent, QGraphicsItem *newGraphicItem)
    : RailwayObject(parent, newGraphicItem)
{
    signalState = SIGNAL_STOP;
    for (int i = 0; i <= SignalState::SIGNAL_CUSTOM8; i++)
    {
        allowedSignalState.push_back(i);
    }
    railActor = nullptr;
}

void Signal::setState(int newSignState, int newSprite)
{
    if (allowedSignalState.indexOf(newSignState) != -1) signalState = newSignState;
    changeSprite(newSprite);
}

int Signal::getState()
{
    return signalState;
}

QList<int> Signal::getAllowedSignalState() const
{
    return allowedSignalState;
}

void Signal::addRailActor(Actor *newRailActor)
{
    railActor = newRailActor;
}

Actor *Signal::getRailActor()
{
    return railActor;
}

Signal::~Signal()
{
    if (railActor != nullptr)
    {
        railActor->actorLeaveFromCollision(dynamic_cast<Actor*>(this));
    }
}

