#include "dependencies/trainnavigation.h"

TrainNavigation::TrainNavigation()
{

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

QList<Rail *> TrainNavigation::autopilotCheck(const int minDistanceCheck, const int minimalPathSegments ,Rail* actualRail, bool direction)
{
    int distanceChecked = 0;
    Rail* testedRail;
    (direction) ? testedRail = actualRail->getConnectedRail(2) : testedRail = actualRail->getConnectedRail(0);

    QList<Rail*> trainPath = {};
    bool condition1 = testedRail != nullptr;
    bool condition2 = distanceChecked < minDistanceCheck || trainPath.size() < minimalPathSegments;
    bool condition3 = distanceChecked < 50000;
    while (condition1 && condition2 && condition3)
    {
        qDebug() << "check path";
        distanceChecked += testedRail->getRailLength();
        trainPath.push_back(testedRail);
        if (direction)
        {
            qDebug() << "1";
            testedRail = testedRail->getConnectedRail(2);
        }
        else
        {
            qDebug() << "2";
            testedRail = testedRail->getConnectedRail(0);
        }
        condition1 = testedRail != nullptr;
        condition2 = distanceChecked < minDistanceCheck || trainPath.size() < minimalPathSegments;
        condition3 = distanceChecked < 50000;
    }
    return trainPath;
}

