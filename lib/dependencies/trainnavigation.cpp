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
        if (signal->getState() == SIGNAL_STOP) return trainPath;
    }

    (direction) ? testedRail = actualRail->getConnectedRail(2) : testedRail = actualRail->getConnectedRail(0);
    if (testedRail != nullptr && (testedRail->getConnection(actualRail) == 2|| testedRail->getConnection(testedRail) == 3)) direction = !direction;

    bool condition1 = testedRail != nullptr;
    bool condition2 = distanceChecked < minDistanceCheck || trainPath.size() < minimalPathSegments;
    bool condition3 = distanceChecked < 50000;

    while (condition1 && condition2 && condition3)
    {

        distanceChecked += testedRail->getRailLength();
        trainPath.push_back(testedRail);

        int endAreaNumber = -1;
        (direction) ? endAreaNumber = 1 : endAreaNumber = 0;

        signal = testedRail->getSignal(endAreaNumber);
        if (signal != nullptr && signal->getState() == SIGNAL_STOP)
        {
            return trainPath; //if signal on end point = 0 -> path end on this signal
        }

        int connectionNumber = 0;
        if (direction) connectionNumber +=2;
        Rail* newConnectedRail = testedRail->getConnectedRail(connectionNumber);
        if (newConnectedRail != nullptr && (newConnectedRail->getConnection(testedRail) == connectionNumber || newConnectedRail->getConnection(testedRail) == connectionNumber +1))
        {
            direction = !direction;
        }
        testedRail = newConnectedRail;


        //new set of conditions
        condition1 = testedRail != nullptr;
        condition2 = distanceChecked < minDistanceCheck || trainPath.size() < minimalPathSegments;
        condition3 = distanceChecked < 50000;
    }
    return trainPath;
}

int TrainNavigation::getTrainPathLength(QList<Rail *> path)
{
    int length = 0;
    for (auto rail : path)
    {
        length += rail->getRailLength();
    }
    return length;
}

bool TrainNavigation::checkDirectionOnLatestRail(QList<Rail *> path, Rail *actualRail, bool actualDirection)
{
    int connection;
    bool direction = 0;
    if (path.size() == 0)
    {
        qDebug() << "1";
        return actualDirection;
    }
    else if (path.size() == 1)
    {
        qDebug() << "2";
        connection = dynamic_cast<Rail*>(path[0])->getConnection(actualRail);
    }
    else
    {
        qDebug() << "3";
        Rail* lastRail = path.last();
        Rail* penultimateRail = path[path.size()-2];
        connection = lastRail->getConnection(penultimateRail);
    }
    (connection <= 1) ? direction = 1 : direction = 0;
    return direction;

}

bool TrainNavigation::checkDirectionOnNextRail(bool actualDirection, Rail *actualRail, Rail* nextRail)
{
    bool direction;
    int conection = nextRail->getConnection(actualRail); //get conection of rail 0-3 (A,B,C,D)
    (conection <= 1) ? direction = true : direction = false; //Transfer connection to direction
    return direction; //transfered to direction
}





