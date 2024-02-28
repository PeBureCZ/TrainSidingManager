#include "actor.h"

Actor::Actor(QObject *parent, QGraphicsItem* newGraphicItem)
    : QObject(parent)
    , graphicItem(newGraphicItem)
{
    name = "default name";
    location = {0,0};
    graphicLocation = {0,0};
    rotation = 0.0f;
    graphicRotation = 0.0f;
    collisionRecieveEnabled = false;
    collisionCallEnabled = false;
    calledCollisions = {};
    triggers = {}; //triggers -> recieve collisions
    actorsInCollision = {};
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
    if (graphicItem != nullptr) graphicItem->setPos(graphicLocation);
}

void Actor::actualizeGraphicRotation()
{
    if (graphicItem != nullptr) graphicItem->setRotation(graphicRotation);
}

void Actor::calledCollisionEvent(const QList<Actor *> isInCollision)
{
    //hidde no longer collided rail
    for (auto actor : actorsInCollision)
    {
        int index = isInCollision.indexOf(actor);
        if (index == -1) actorLeaveFromCollision(actor); //is no longer in actorsInCollision QList
    }

    //show newly collided rail
    for (auto actor : isInCollision)
    {
        int index = actorsInCollision.indexOf(actor);
        if (index == -1) actorEnterInCollision(actor);//actor is not in holdedRail QList -> need add
    }
}

void Actor::actorLeaveFromCollision(Actor* actor)
{
    actorsInCollision.removeOne(actor);
}

void Actor::actorEnterInCollision(Actor *actor)
{
    actorsInCollision.push_back(actor);
}

QGraphicsItem *Actor::getGraphicItem()
{
    return graphicItem;
}

QPoint Actor::getGraphicLocation()
{
    return graphicLocation;
}

void Actor::setName(QString newName)
{
    name = newName;
}

QString Actor::getName()
{
    return name;
}

void Actor::setRotation(const float newRotation, bool setGraphic)
{
    rotation = newRotation;
    if (setGraphic)
    {
        setGraphicRotation(newRotation);
        actualizeGraphicRotation();
    }
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

void Actor::setLocation(QPointF newLocation, bool setGraphic)
{
    setLocation(newLocation.toPoint(), setGraphic);
}

QPoint Actor::getLocation()
{
    return location;
}

QPoint Actor::getRotatedPointArountPivot(const QPoint point, const QPoint pivot, const double angle)
{
    float radian = angle * M_PI / 180.0;

    int newX = round((point.x() - pivot.x()) * cos(radian) - (point.y() - pivot.y()) * sin(radian) + pivot.x());
    int newY = round((point.x() - pivot.x()) * sin(radian) + (point.y() - pivot.y()) * cos(radian) + pivot.y());
    QPoint newPoint = QPoint(newX, newY);
    return newPoint;
}

QVector<Trigger*> Actor::getAllTriggers()
{
    return triggers;
}

void Actor::setGraphicRotation(const float newRotation)
{
    graphicRotation = newRotation;
}

void Actor::createTriggerInActor(int indexOfType, QVector<int> channels, QPoint relativeLocation, float relativeRotation, int radius)
{
    //DO NOT USE THIS FUNCTION WITHOUT SAVING COLLIDE CHANNELS TO WORLD COLLIDE LISTS!
    //USE WorldCollide class!
    collisionRecieveEnabled = true;
    Trigger* component = {};
    switch (indexOfType)
    {
        case SPHERE_COLLIDER:
        {
            Trigger* newComponent = new SphereCollider();
            dynamic_cast<SphereCollider*>(newComponent)->setRadius(radius);
            component = newComponent;
            break;
        }
        case BOX_COLLIDER:
        {
            Trigger* newComponent = new BoxCollider();
            QPoint leftUpCorner = relativeLocation + QPoint(relativeLocation.x() - radius/2, relativeLocation.y() - radius/2);
            QPoint rightDownCorner = relativeLocation + QPoint(relativeLocation.x() + radius/2, relativeLocation.y() + radius/2);
            dynamic_cast<BoxCollider*>(newComponent)->setBoxCollider(leftUpCorner, rightDownCorner, relativeRotation);
            component = newComponent;
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

void Actor::changeSprite(int spriteFromEnum)
{
    if (dynamic_cast<QGraphicsPixmapItem*>(graphicItem))
    {
        SpriteColection newSprite;
        QPixmap pixmap = newSprite.getSprite(spriteFromEnum);
        dynamic_cast<QGraphicsPixmapItem*>(graphicItem)->setPixmap(pixmap);
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

void Actor::setRailObjectBoxCollider()
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
    if (graphicItem != nullptr) delete graphicItem;
}




