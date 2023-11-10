#include "actor.h"


Actor::Actor()
{
    name = "default name";
    location = {0,0};
    rotation = 0.0f;
}

void Actor::setName(QString newName)
{
    name = newName;
}

QString Actor::getName()
{
    return name;
}

void Actor::setRotation(float newRotation)
{
    rotation = newRotation;
}

void Actor::setLocation(QPoint newLocation)
{
    location = newLocation;
}

QPoint Actor::getLocation()
{
    return location;
}

Actor::~Actor()
{
}




