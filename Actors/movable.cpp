#include "movable.h"

Movable::Movable(QObject* parent, QGraphicsItem* newGraphicItem) : Actor(parent, newGraphicItem)
{
    maxSpeed =0; //centimeters per tick (1 km/h = 27.778 cm/s), tick = 1 second
    actualSpeed = 0; //centimeters per tick
}

void Movable::setActualSpeed(int newSpeed)
{
    if (newSpeed <= maxSpeed) actualSpeed = newSpeed;
    else actualSpeed = maxSpeed;
}

int Movable::getMaxSpeed()
{
    return maxSpeed;
}

/*
Movable::virtual ~Movable()
{

}

*/
