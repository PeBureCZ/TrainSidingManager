#ifndef RAIL_H
#define RAIL_H

#include "railwayobject.h"
#include <QGraphicsPathItem>

class Rail : public RailwayObject
{
protected:
    QGraphicsPathItem* path;
public:
    Rail(QGraphicsPathItem* pathObj);
};

#endif // RAIL_H
