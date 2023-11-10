#ifndef ACTORCONSTRUCTOR_H
#define ACTORCONSTRUCTOR_H

#include "actor.h"

class ActorConstructor : public Actor
{
public:
    ActorConstructor();
    virtual void actualizeConstructor(QPoint newPoint);
};

#endif // ACTORCONSTRUCTOR_H
