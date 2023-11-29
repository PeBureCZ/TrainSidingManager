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
    Trigger* component = {};
    switch (indexOfType)
    {
        case 0: //SphereCollider
        {
            Trigger* newComponent = new SphereCollider();
            dynamic_cast<SphereCollider*>(newComponent)->setRadius(1000);
            component = newComponent;
            break;
        }
        case 1: //BoxCollider
        {
            Trigger* newComponent = new BoxCollider();
            component = newComponent;
            break;
        }
        case 2:
        {
            break;
        }
        defaul: {}
    }
    if (component != nullptr)
    {
        component->setRelativeLocation(relativeLocation);
        component->setRelativeRotation(relativeRotation);
        component->setBlockChannels(channels);
        triggers.push_back(component);
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

void Actor::setObjectBoxCollider()
{
    //overrided
}

void Actor::tickEvent()
{
    //overrided
}

Actor::~Actor()
{
    for (auto trigger : triggers)
    {
        delete trigger;
    }
    delete graphicItem;
}




