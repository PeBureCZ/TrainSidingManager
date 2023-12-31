#include "actor.h"

Actor::Actor(QObject *parent, QGraphicsItem* newGraphicItem) : QObject(parent), graphicItem(newGraphicItem)
{
    name = "default name";
    location = {0,0};
    graphicLocation = {0,0};
    rotation = 0.0f;
    collisionRecieveEnabled = false;
    collisionCallEnabled = false;
    calledCollisions = {};
    triggers = {}; //triggers -> recieve collisions
}

void Actor::setGraphicLocation(QPoint newLocation)
{
    //This function is called from QThread. The visual change is made in the main thread (in the WorldMap)
    //by function "actualizeGraphicLocation()"
    graphicLocation = newLocation;
}

void Actor::actualizeGraphicLocation()
{
    //this function is called from world with function "updateWorld"
    //location (graphicLocation variable) is changed in QThreads and have to be changed in main thread
    graphicItem->setPos(graphicLocation);
}

void Actor::actorCollide(const QList<Actor *> actorsInCollision)
{
    //overrided
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

void Actor::setRotation(const float newRotation)
{
    rotation = newRotation;
}

void Actor::setCallCollisionChannels(const QVector<int> newCollisions)
{
    calledCollisions = newCollisions;
    if (newCollisions.size() > 0) collisionCallEnabled = true;
    else collisionCallEnabled = false;
}

void Actor::setLocation(QPoint newLocation, bool setGraphic)
{
    location = newLocation;
    if (setGraphic)
    {
        setGraphicLocation(newLocation);
        actualizeGraphicLocation();
    }
}

QPoint Actor::getLocation()
{
    return location;
}

QVector<Trigger*> Actor::getAllTriggers()
{
    return triggers;
}

void Actor::addTriggerComponent(int indexOfType, QVector<int> channels, QPoint relativeLocation, float relativeRotation, int radius)
{
    //for recieve collision ONLY!!!
    collisionRecieveEnabled = true;
    Trigger* component = {};
    switch (indexOfType)
    {
        case 0: //SphereCollider
        {
            Trigger* newComponent = new SphereCollider();
            dynamic_cast<SphereCollider*>(newComponent)->setRadius(radius);
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

int Actor::getDistance(QPoint pointA, QPoint pointB)
{
    QLineF line(pointA, pointB);
    return line.length();
}

QVector<int> Actor::recieveCollideChannels()
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

QVector<int> Actor::callCollideChannels()
{
    return calledCollisions;
}

bool Actor::canRecieveCollision()
{
    return collisionRecieveEnabled;
}

bool Actor::canCallCollision()
{
    return collisionCallEnabled;
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




