#include "actor.h"


Actor::Actor(QGraphicsItem* newGraphicItem) : graphicItem(newGraphicItem)
{
    name = "default name";
    location = {0,0};
    rotation = 0.0f;
    triggers = {};
    collisionEnabled = false;
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

QVector<Trigger*> Actor::getAllTriggers()
{
    return triggers;
}

void Actor::addTriggerComponent(int indexOfType, QVector<int> channels, QPoint relativeLocation, float relativeRotation)
{
    collisionEnabled = true;
    switch (indexOfType)
    {
    case 0: //SphereCollider
    {
        Trigger* newComponent = new SphereCollider();
        newComponent->setRelativeLocation(relativeLocation);
        newComponent->setRelativeRotation(relativeRotation);
        newComponent->setBlockChannels(channels);
        triggers.push_back(newComponent);
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

QVector<int> Actor::getCollideChannels()
{
    QVector<int> allChannelsUsed = {};
    QVector<int> testedChannels = {};
    for (auto trigger : triggers)
    {
        testedChannels = trigger->getBlockChannels();
        for (auto channel : testedChannels)
        {
            if (allChannelsUsed.indexOf(channel) == -1)
            {
            allChannelsUsed.push_back(channel);
            }
        }
    }
    return allChannelsUsed;
}

bool Actor::canCollide()
{
    return collisionEnabled;
}

Actor::~Actor()
{
    for (auto trigger : triggers)
    {
        delete trigger;
    }
    delete graphicItem;
}




