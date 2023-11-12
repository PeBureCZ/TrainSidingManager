#ifndef VEHICLE_H
#define VEHICLE_H

#include "movable.h"

class Vehicle : public Movable
{
protected:
    int mass; //in kg
    int width; //decimetre
    int length; //decimetre
    QPoint firstAxleCenter; //relative
    int secondAxleDistance; //relative
    int actualSpeed;
public:
    Vehicle();
    QPoint onAxlePos();
};

#endif //VEHICLE_H
