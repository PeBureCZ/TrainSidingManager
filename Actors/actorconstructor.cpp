#include "actorconstructor.h"

ActorConstructor::ActorConstructor(Actor *actorToConstructing) : actorConstructing (actorToConstructing)
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
