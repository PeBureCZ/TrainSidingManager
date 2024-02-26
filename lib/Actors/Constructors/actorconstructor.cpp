#include "actorconstructor.h"

ActorConstructor::ActorConstructor(QObject* parent, QGraphicsItem* newGraphicItem, Actor *actorToConstructing)
    : Actor(parent, newGraphicItem)
    , actorConstructing (actorToConstructing)
{
    zoomLevelSaved = 0;
}

void ActorConstructor::actualizeConstructor(QPoint newPoint, int zoomLevel)
{
    //overrided in subclass
    zoomLevelSaved = zoomLevel;
    setLocation(newPoint,false);
}

Actor *ActorConstructor::getActorConstructing()
{
    return actorConstructing;
}

Actor *ActorConstructor::setActorConstructing(Actor * newActor)
{
    actorConstructing = newActor;
}
