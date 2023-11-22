#ifndef TRAINNAVIGATION_H
#define TRAINNAVIGATION_H

#include "Actors/rail.h"

class TrainNavigation
{
public:
    TrainNavigation();
    bool checkNewDirection(bool actualDirection, Rail* actualRail, Rail* newRail);
};

#endif // TRAINNAVIGATION_H
