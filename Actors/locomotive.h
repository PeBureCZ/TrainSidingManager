#ifndef LOCOMOTIVE_H
#define LOCOMOTIVE_H

#include "vehicle.h"

class Locomotive : public Vehicle
{
protected:
    int power;
public:
    Locomotive(QGraphicsItem* newGraphicItem);
};

#endif // LOCOMOTIVE_H
