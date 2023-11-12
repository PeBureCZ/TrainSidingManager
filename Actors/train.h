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
    int onPathLength;
public:
    Train(Rail* spawnedRail);
    float getActualPathValue();
    void setActualPathValue(float newValue);

    int getActualLengthOnPath();
    void setActualLengthOnPath(int newValue);

    void setActualPath(QGraphicsPathItem* newPath);
    QGraphicsPathItem* getActualPath();
    QPointF getLocationOnPath(float percentOnPath);
};

#endif // TRAIN_H
