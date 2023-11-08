#ifndef TRAIN_H
#define TRAIN_H

#include "movable.h"
#include <QGraphicsPathItem>
#include "rail.h"

class Train : public Movable
{
protected:
    QGraphicsPathItem* actualPath;
    Rail* actualRail;
    float onPathValue;
public:
    Train(Rail* spawnedRail);
    float getActualPathValue();
    void setActualPathValue(float newValue);
    void setActualPath(QGraphicsPathItem* newPath);
    QGraphicsPathItem* getActualPath();
    QPointF getLocationOnPath(float percentOnPath);
};

#endif // TRAIN_H
