#include "vehicle.h"


Vehicle::Vehicle()
{
    mass = 0;
    firstAxleCenter = {0,0};
    secondAxleDistance = 0;
    actualSpeed = 0;
    width = 0;
    length = 0;
}

QPoint Vehicle::onAxlePos()
{
    QPoint axlePos = location - firstAxleCenter;
    return axlePos;
}



