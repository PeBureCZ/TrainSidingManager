#ifndef VEHICLE_H
#define VEHICLE_H

#include "movable.h"

class Vehicle : public Movable
{
protected:
    int mass; //in kg
public:
    Vehicle();
};

#endif //VEHICLE_H
