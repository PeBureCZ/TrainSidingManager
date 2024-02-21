#include "actorconstructor.h"

ActorConstructor::ActorConstructor(QObject* parent, QGraphicsItem* newGraphicItem, Actor *actorToConstructing)
    : Actor(parent, newGraphicItem)
    , actorConstructing (actorToConstructing)
{
}

void ActorConstructor::actualizeConstructor(QPoint newPoint)
{
    //overrided in subclass
}

Actor *ActorConstructor::getActorConstructing()
{
    return actorConstructing;
}

Actor *ActorConstructor::setActorConstructing(Actor * newActor)
{
    actorConstructing = newActor;
}
