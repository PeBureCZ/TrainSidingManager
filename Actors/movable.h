#ifndef MOVABLE_H
#define MOVABLE_H

#include "actor.h"
#include <QGraphicsPathItem>

class Movable : public Actor
{
protected:
    int maxSpeed;


public:
    Movable();

    //virtual ~Movable();
};

#endif // MOVABLE_H
