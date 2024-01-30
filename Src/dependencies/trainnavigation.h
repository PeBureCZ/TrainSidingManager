
#ifndef TRAINNAVIGATION_H
#define TRAINNAVIGATION_H

#include "Actors/rail.h"



class TrainNavigation
{
public:
    //TrainNavigation();
    static bool checkNewDirection(bool actualDirection, Rail* actualRail, Rail* newRail);
    static QList<Rail*> autopilotCheck(int minDistanceCheck, const int minimalPathSegments, Rail *actualRail, bool direction);

};

#endif // TRAINNAVIGATION_H
