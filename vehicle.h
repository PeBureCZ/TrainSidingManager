#ifndef TRAIN_H
#define TRAIN_H

#include "movable.h"
#include <QGraphicsPathItem>

class Vehicle : public Movable
{
protected:
    QGraphicsPathItem* path;
public:
    Vehicle();
    void addPath(QGraphicsPathItem *pathItem);
    void movePath(float startPercent);
};

#endif // TRAIN_H
