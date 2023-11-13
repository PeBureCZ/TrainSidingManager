#include "actorconstructor.h"

ActorConstructor::ActorConstructor(QGraphicsItem* newGraphicItem, Actor *actorToConstructing)
:Actor(newGraphicItem)
,actorConstructing (actorToConstructing)
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
