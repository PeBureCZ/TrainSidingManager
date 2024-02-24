#ifndef TRAINNAVIGATION_H
#define TRAINNAVIGATION_H

#include "Actors/rail.h"

class LIB_EXPORT TrainNavigation
{
public:
    static bool checkDirectionOnNextRail(bool actualDirection, Rail* actualRail, Rail* newRail);
    static QList<Rail*> autopilotCheck(int minDistanceCheck, const int minimalPathSegments, Rail *actualRail, bool direction);
    static int getTrainPathLength(QList<Rail*> path);
    static bool checkDirectionOnLatestRail(QList<Rail*> path, Rail* actualRail, bool actualDirection);
};

#endif // TRAINNAVIGATION_H
