#ifndef MOVABLE_H
#define MOVABLE_H

#include "actor.h"
#include <QGraphicsPathItem>

class Movable : public Actor
{
protected:
    QGraphicsPathItem* pathItem;

public:
    Movable();
    void addPath(QGraphicsPathItem *pathItemObj);
    QPointF getLocationOnPath(float percentOnPath);
    //~Movable();
};

#endif // MOVABLE_H
