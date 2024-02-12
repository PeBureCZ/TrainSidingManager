#include "dependencies/trainnavigation.h"

QList<Rail *> TrainNavigation::autopilotCheck(const int minDistanceCheck, const int minimalPathSegments ,Rail* actualRail, bool direction)
{
    int distanceChecked = 0;
    Rail* testedRail;
    QList<Rail*> trainPath = {};
    Signal* signal = nullptr;
    (direction) ? signal = actualRail->getSignal(1) : signal = actualRail->getSignal(0);

    //autopilot end on red signal state
    if (signal != nullptr)
    {
        if (signal->getState() == 0) return trainPath;
    }

    (direction) ? testedRail = actualRail->getConnectedRail(2) : testedRail = actualRail->getConnectedRail(0);
    if (testedRail != nullptr && (testedRail->getConnection(actualRail) == 2|| testedRail->getConnection(testedRail) == 3)) direction = !direction;

    bool condition1 = testedRail != nullptr;
    bool condition2 = distanceChecked < minDistanceCheck || trainPath.size() < minimalPathSegments;
    bool condition3 = distanceChecked < 50000;

    //
    while (condition1 && condition2 && condition3)
    {
        distanceChecked += testedRail->getRailLength();
        trainPath.push_back(testedRail);

        int connectionNumber = 0;
        if (direction) connectionNumber +=2;
        Rail* newConnectedRail = testedRail->getConnectedRail(connectionNumber);
        if (newConnectedRail != nullptr && (newConnectedRail->getConnection(testedRail) == connectionNumber || newConnectedRail->getConnection(testedRail) == connectionNumber +1))
        {
            direction = !direction;
        }
        testedRail = newConnectedRail;

        int endAreaNumber = -1;
        (direction) ? endAreaNumber = 1 : endAreaNumber = 0;

        if (testedRail != nullptr)
        {
            signal = testedRail->getSignal(endAreaNumber);
            if (signal != nullptr)
            {
                if (signal->getState() == 0)
                {
                    trainPath.push_back(testedRail);
                    return trainPath; //if signal on end point = 0 -> path end on this signal
                }
            }
        }
        else signal = nullptr;

        //new set of conditions
        condition1 = testedRail != nullptr;
        condition2 = distanceChecked < minDistanceCheck || trainPath.size() < minimalPathSegments;
        condition3 = distanceChecked < 50000;
    }
    return trainPath;
}

bool TrainNavigation::checkNewDirection(bool actualDirection, Rail *actualRail, Rail* newRail)
{
    QPoint railEndPosition;
    if (actualDirection) // direction = from P0 to P3
    {
        railEndPosition = actualRail->getLocation() + actualRail->getP3RelativeLocation().toPoint(); //P3
        if (railEndPosition != newRail->getLocation()) return false; //if true: end P3 -> start P3, false = change direction
    }
    else // direction = from P3 to P0
    {
      railEndPosition = actualRail->getLocation(); //P0
      if (railEndPosition != newRail->getLocation()) return false; //if true: end P0 -> start P3, false = same direction as before
    }
    return true; //set direction to "from P0 to P3" = "directionToEnd" in Train(Actor)
}



