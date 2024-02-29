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

        distanceChecked += testedRail->getLengthOfRail();
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
        length += rail->getLengthOfRail();
    }
    return length;
}

bool TrainNavigation::checkDirectionOnLatestRail(const QList<Rail *> path, const Rail *actualRail, bool actualDirection)
{
    int connection;
    bool direction = 0;
    if (path.size() == 0)
    {
        return actualDirection;
    }
    else if (path.size() == 1) connection = dynamic_cast<Rail*>(path[0])->getConnection(actualRail);
    else
    {
        Rail* lastRail = path.last();
        Rail* penultimateRail = path[path.size()-2];
        connection = lastRail->getConnection(penultimateRail);
    }
    (connection <= 1) ? direction = 1 : direction = 0;
    return direction;

}

void TrainNavigation::checkObjectsOnPath(const Rail* actualRail, const QList<Rail*> actualPath, bool direction, int distanceToEnd)
{
    //check a signals on the actualRail
    QList<Signal*> signalsOnPath = {};
    QList<int> signalOnDistant = {};
    int railEnd = 0;
    int distanceMeasure = 0;
    if (direction) railEnd++;
    distanceMeasure += actualRail->getLengthOfRail();
    if (actualRail->getSignal(railEnd) != nullptr) signalsOnPath.push_back(actualRail->getSignal(railEnd));
    if (signalsOnPath.size() != 0) signalOnDistant.push_back(distanceMeasure);

    //check a signals on remaining train path
    if (actualPath.size() == 0) return;
    //actualize train direction from actualRail to firstPath
    direction = TrainNavigation::checkDirectionOnNextRail(direction, actualRail, actualPath[0]);
    int railIndex = 0;
    for (auto rail : actualPath)
    {
        distanceMeasure += rail->getLengthOfRail();
        railEnd = 0;
        if (direction) railEnd++;
        if (rail->getSignal(railEnd) != nullptr)
        {
            signalOnDistant.push_back(distanceMeasure);
            signalsOnPath.push_back(rail->getSignal(railEnd));
        }
        if (railIndex < actualPath.size()-1) direction = TrainNavigation::checkDirectionOnNextRail(direction, rail, actualPath[railIndex+1]);
        railIndex++;
    }

    qDebug() << "signals on path: " << signalsOnPath.size();

    int signalsCount = signalsOnPath.size();
    if (signalsCount > 0) signalsOnPath.last()->setState(SIGNAL_STOP, STOP_SIGNAL_SPRITE);
    if (signalsCount > 1)
    {
        if (distanceToEnd < distanceMeasure - signalOnDistant[signalsCount-2]) dynamic_cast<Signal*>(signalsOnPath[signalsCount-2])->setState(SIGNAL_CAUTION, CAUTION_SIGNAL_SPRITE);
        else dynamic_cast<Signal*>(signalsOnPath[signalsCount-2])->setState(SIGNAL_STOP, STOP_SIGNAL_SPRITE);
    }

    if (signalsCount > 2)
    {
        for (int i = 0; i < signalsCount-2; i++)
        {
            qDebug() << "DTE: " << distanceToEnd << "    SIGoD: " << signalOnDistant[i] << "    mes: " << distanceMeasure;
            if (distanceToEnd < distanceMeasure - signalOnDistant[i]) dynamic_cast<Signal*>(signalsOnPath[i])->setState(SIGNAL_PROCEED, PROCEED_SIGNAL_SPRITE);
            else dynamic_cast<Signal*>(signalsOnPath[i])->setState(SIGNAL_STOP, STOP_SIGNAL_SPRITE);
        }
    }
}

bool TrainNavigation::checkDirectionOnNextRail(bool actualDirection, const Rail *actualRail, const Rail *nextRail)
{
    bool direction;
    int conection = nextRail->getConnection(actualRail); //get conection of rail 0-3 (A,B,C,D)
    (conection <= 1) ? direction = true : direction = false; //Transfer connection to direction
    return direction; //transfered to direction
}





