#include "signal.h"



Signal::Signal(QObject *parent, QGraphicsItem *newGraphicItem)
    : RailwayObject(parent, newGraphicItem)
{
    signalState = 0;
    for (int i = 0; i <= SignalState::SIGNAL_CUSTOM8; i++)
    {
        allowedSignalState.push_back(i);
    }
}

void Signal::setState(int newSignState)
{
    if (allowedSignalState.indexOf(newSignState) != -1) signalState = newSignState;
}

int Signal::getState()
{
    return signalState;
}

QList<int> Signal::getAllowedSignalState() const
{
    return allowedSignalState;
}

Signal::~Signal()
{}

