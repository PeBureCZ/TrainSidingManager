#include "movable.h"

Movable::Movable()
{
    pathItem = {};
}

void Movable::addPath(QGraphicsPathItem* pathItemObj)
{
    pathItem = pathItemObj;
}

QGraphicsPathItem *Movable::getPath()
{
    return pathItem;
}

QPointF Movable::getLocationOnPath(float percentOnPath)
{
    QPointF newPoint = pathItem->path().pointAtPercent(percentOnPath);
    return newPoint;
}


/*
Movable::~Movable()
{
    pixmapItem->setPos(-500,-500);
}

*/
