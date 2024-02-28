#ifndef MOVABLE_H
#define MOVABLE_H

#include "actor.h"

class LIB_EXPORT Movable : public Actor
{
Q_OBJECT
protected:
    float maxSpeed;
    float actualSpeed;


public:
    Movable(QObject *parent = nullptr, QGraphicsItem* newGraphicItem = nullptr);
    void setActualSpeed(float newSpeed);
    float getMaxSpeed();
    void setMaxSpeed(float newMaxSpeed);

    const float getActualSpeed();

signals:

public slots:


};

#endif // MOVABLE_H
