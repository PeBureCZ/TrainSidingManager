#ifndef RAILWAYOBJECT_H
#define RAILWAYOBJECT_H

#include "actor.h"

class RailwayObject : public Actor
{
protected:
    bool visibleName;
public:
    RailwayObject(QGraphicsItem* newGraphicItem);
};

#endif // RAILWAYOBJECT_H
