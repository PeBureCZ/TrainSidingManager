#ifndef TRAIN_H
#define TRAIN_H

#include "movable.h"

class Vehicle : public Movable
{
public:
    Vehicle();
    void addPath();
    void movePath(float startPercent);
};

#endif // TRAIN_H
