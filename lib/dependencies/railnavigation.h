#ifndef RAILNAVIGATION_H
#define RAILNAVIGATION_H

#include "Actors/train.h"
#include "Actors/rail.h"

class LIB_EXPORT RailNavigation
{
public:
    static void makePath(Train* train, Signal *nearestSignal);
};

#endif // RAILNAVIGATION_H
