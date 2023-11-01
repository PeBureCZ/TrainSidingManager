#include "actor.h"

Actor::Actor()
{
    name = "default name";
    location = {0,0};
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

//Actor::~Actor()
//{

//}


