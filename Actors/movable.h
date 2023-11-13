#ifndef MOVABLE_H
#define MOVABLE_H

#include "actor.h"

class Movable : public Actor
{
protected:
    int maxSpeed;
    int actualSpeed;


public:
    Movable(QGraphicsItem* newGraphicItem);
    void setActualSpeed(int newSpeed);
    int getMaxSpeed();

    //virtual ~Movable();
};

#endif // MOVABLE_H
