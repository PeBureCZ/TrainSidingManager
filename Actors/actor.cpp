#include "actor.h"


Actor::Actor(QGraphicsItem* newGraphicItem) : graphicItem(newGraphicItem)
{
    name = "default name";
    location = {0,0};
    rotation = 0.0f;
    triggers = {};
    collisionEnabled = false;
    worldCollideObject = nullptr;
}

QGraphicsItem *Actor::getGraphicItem()
{
    return graphicItem;
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

void Actor::addTriggerComponent(QPoint relativeLocation, float relativeRotation, int indexOfType, QVector<int> channels)
{
    if (collisionEnabled = true)
    {
        switch (indexOfType)
        {
        case 0:
        {
            Trigger* newComponent = new SphereCollider();
            triggers.push_back(newComponent);
            for (auto channel : channels)
            {
                worldCollideObject->addTriggerToList(newComponent, channel);
            }

            break;
        }
        case 1:
        {
            break;
        }
        case 2:
        {
            break;
        }
        defaul: {}
        }
    }
}

void Actor::enableCollision(WorldCollide* collisionObject)
{
    worldCollideObject = collisionObject;
    collisionEnabled = true;
}

Actor::~Actor()
{
    for (auto trigger : triggers)
    {
        delete trigger;
    }
    delete graphicItem;
}




