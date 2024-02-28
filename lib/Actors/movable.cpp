#include "movable.h"


Movable::Movable(QObject* parent, QGraphicsItem* newGraphicItem) : Actor(parent, newGraphicItem)
{
    maxSpeed =0.0f; //decimeters per tick (1 km/h = 2.7778 cm/s), tick = 200ms (0.2s)
    actualSpeed = 0.0f; //decimeters per tick (200ms)
}

void Movable::setActualSpeed(float newSpeed)
{
    if (newSpeed <= maxSpeed) actualSpeed = newSpeed;
    else actualSpeed = maxSpeed;
    if (actualSpeed < 0.0f) actualSpeed = 0.0f;
}

float Movable::getMaxSpeed()
{
    return maxSpeed;
}

void Movable::setMaxSpeed(float newMaxSpeed)
{
    maxSpeed = newMaxSpeed;
}

const float Movable::getActualSpeed()
{
    return actualSpeed;
}

/*
Movable::virtual ~Movable()
{

}

*/
