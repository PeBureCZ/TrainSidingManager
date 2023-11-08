#ifndef TRAIN_H
#define TRAIN_H

#include "movable.h"
#include <QGraphicsPathItem>

class Train : public Movable
{
protected:
    QGraphicsPathItem* actualPath;
    float onPathValue;
public:
    Train();
    float getActualPathValue();
    void setActualPathValue(float newValue);
    void setActualPath(QGraphicsPathItem* newPath);
    QGraphicsPathItem* getActualPath();
    QPointF getLocationOnPath(float percentOnPath);
};

#endif // TRAIN_H
