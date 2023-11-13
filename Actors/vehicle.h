#ifndef VEHICLE_H
#define VEHICLE_H

#include "movable.h"

class Vehicle : public Movable
{
protected:
    int mass; //kg
    int width; //decimeter
    int length; //decimeter
    QPoint firstAxleCenter; //relative
    int secondAxleDistance; //relative
public:
    Vehicle(QGraphicsItem* newGraphicItem);
    QPoint axlePos();
};

#endif //VEHICLE_H
