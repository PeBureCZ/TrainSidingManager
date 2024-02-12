#include "railwayobject.h"


RailwayObject::RailwayObject(QObject* parent, QGraphicsItem* newGraphicItem) : Actor(parent, newGraphicItem)
{
    visibleName = false;
}

