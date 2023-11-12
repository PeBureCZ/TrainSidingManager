#ifndef VEHICLE_H
#define VEHICLE_H

#include "movable.h"

class Vehicle : public Movable
{
protected:
    int mass; //in kg
    QPoint firstAxleCenter; //relative
    QPoint secondAxleCenter; //relative
    int actualSpeed;
public:
    Vehicle();
};

#endif //VEHICLE_H
