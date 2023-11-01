#include "actor.h"

Actor::Actor()
{
    name = "default name";
    location = {0,0};
    rotation = 0.0f;
    worldScene;
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

void Actor::destroyActor()
{
    delete this;
}


