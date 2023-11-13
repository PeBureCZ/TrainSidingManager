#include "rail.h"

Rail::Rail(QGraphicsItem* newGraphicItem) : RailwayObject(newGraphicItem)
{
    P0 = {0,0};
    P1 = {0,0};
    P2 = {0,0};
    P3 = {0,0};
}

QPointF Rail::getP0Point()
{
    return {P0};
}

QPointF Rail::getP1Point()
{
    return {P1};
}

QPointF Rail::getP2Point()
{
    return {P2};
}

QPointF Rail::getP3Point()
{
    return {P3};
}

void Rail::setP0(QPoint newPoint)
{
    P0 = newPoint;
}

void Rail::setP1(QPoint newPoint)
{
    P1 = newPoint;
}

void Rail::setP2(QPoint newPoint)
{
    P2 = newPoint;
}

void Rail::setP3(QPoint newPoint)
{
    P3 = newPoint;
}

