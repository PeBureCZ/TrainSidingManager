#include "movable.h"


Movable::Movable(QObject* parent, QGraphicsItem* newGraphicItem) : Actor(parent, newGraphicItem)
{
    maxSpeed =0; //decimeters per tick (1 km/h = 2.7778 cm/s), tick = 200ms (0.2s)
    actualSpeed = 0; //decimeters per tick (200ms)
}

void Movable::setActualSpeed(int newSpeed)
{
    if (newSpeed <= maxSpeed) actualSpeed = newSpeed;
    else actualSpeed = maxSpeed;
    if (actualSpeed < 0) actualSpeed = 0;
}

int Movable::getMaxSpeed()
{
    return maxSpeed;
}

void Movable::setMaxSpeed(int newMaxSpeed)
{
    maxSpeed = newMaxSpeed;
}

const int Movable::getActualSpeed()
{
    return actualSpeed;
}

/*
Movable::virtual ~Movable()
{

}

*/
