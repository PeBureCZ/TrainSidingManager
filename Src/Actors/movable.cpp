#include "movable.h"



Movable::Movable(QObject* parent, QGraphicsItem* newGraphicItem) : Actor(parent, newGraphicItem)
{
    maxSpeed =0; //decimeters per tick (1 km/h = 2.7778 cm/s), tick = 1 second
    actualSpeed = 0; //decimeters per tick (1 second)
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

void Movable::setMaxSpeed(int newMaxSpeed)
{
    maxSpeed = newMaxSpeed;
}

/*
Movable::virtual ~Movable()
{

}

*/
