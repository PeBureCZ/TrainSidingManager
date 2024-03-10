#ifndef TRAINNAVIGATION_H
#define TRAINNAVIGATION_H

#include "Actors/rail.h"

class LIB_EXPORT TrainNavigation
{
public:
    static bool checkDirectionOnNextRail(bool actualDirection, const Rail* actualRail, const Rail* newRail);
    static QList<Rail*> autopilotCheck(int minDistanceCheck, const int minimalPathSegments, Rail *actualRail, bool direction);
    static int getTrainPathLength(QList<Rail*> path);
    static bool checkDirectionOnLatestRail(const QList<Rail*> path, const Rail* actualRail, bool actualDirection);
    static void checkSignalsOnPath(const bool shunt, const Rail *actualRail, const QList<Rail *> actualPath, bool direction, int distanceToEnd);
};

#endif // TRAINNAVIGATION_H
