#ifndef TRAINNAVIGATION_H
#define TRAINNAVIGATION_H

#include "Actors/train.h"
#include "Actors/rail.h"

class TrainNavigation
{
private:
    Rail* actualRail;
    Train* train;
public:
    TrainNavigation(Train* trainObject, Rail* destinationRail);
    QVector<Rail*> makePath();
};

#endif // TRAINNAVIGATION_H
