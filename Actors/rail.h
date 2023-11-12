#ifndef RAIL_H
#define RAIL_H

#include "railwayobject.h"
#include <QGraphicsPathItem>

class Rail : public RailwayObject
{
protected:
    QGraphicsPathItem* path;
    QPoint P0; //start point - ABSOLUTE
    QPoint P1; //first curve control point - RELATIVE TO P0
    QPoint P2; //second curve control point - RELATIVE TO P0
    QPoint P3; //end point - RELATIVE TO P0
public:
    Rail(QGraphicsPathItem* pathObj);
    QGraphicsPathItem* getPathItem();
    QPointF getP0Point();
    QPointF getP1Point();
    QPointF getP2Point();
    QPointF getP3Point();
    void setP0(QPoint newPoint);
    void setP1(QPoint newPoint);
    void setP2(QPoint newPoint);
    void setP3(QPoint newPoint);
};

#endif // RAIL_H