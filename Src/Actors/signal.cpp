#include "signal.h"

Signal::Signal(QObject *parent, QGraphicsItem *newGraphicItem)
    : RailwayObject(parent, newGraphicItem)
{
    signalState = 0;
    allowedSignalState = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15};
}

void Signal::setState(int newSignState)
{
    if (allowedSignalState.indexOf(newSignState) != -1) signalState = newSignState;
}

int Signal::getState()
{
    return signalState;
}


Signal::~Signal()
{}

