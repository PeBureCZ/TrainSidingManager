#ifndef RAILNAVIGATION_H
#define RAILNAVIGATION_H

#include "Actors/train.h"
#include "Actors/rail.h"

class LIB_EXPORT RailNavigation
{
private:
    Rail* actualRail;
    Train* train;
public:
    RailNavigation(Train* trainObject, Rail* destinationRail);
    QVector<Rail*> makePath();
};

#endif // RAILNAVIGATION_H
