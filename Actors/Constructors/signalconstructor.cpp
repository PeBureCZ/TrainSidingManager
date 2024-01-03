#include "signalconstructor.h"

SignalConstructor::SignalConstructor(QObject* parent, QGraphicsItem* newGraphicItem, Actor *actorToConstructing)
    : RailobjectConstructor(parent, newGraphicItem, actorToConstructing)
{

}

void SignalConstructor::actualizeConstructor(QPoint newPoint)
{
    QPoint slideLocation = {5,-50};
    setLocation(newPoint + slideLocation, true);
}

SignalConstructor::~SignalConstructor(){}


