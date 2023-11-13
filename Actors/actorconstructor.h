#ifndef ACTORCONSTRUCTOR_H
#define ACTORCONSTRUCTOR_H

#include "actor.h"

class ActorConstructor : public Actor
{
protected:
    Actor* actorConstructing;
public:
    ActorConstructor(QGraphicsItem *newGraphicItem, Actor* actorToConstructing);
    virtual void actualizeConstructor(QPoint newPoint);
    Actor *getActorConstructing();
};

#endif // ACTORCONSTRUCTOR_H
