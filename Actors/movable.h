#ifndef MOVABLE_H
#define MOVABLE_H

#include "actor.h"

class Movable : public Actor
{
Q_OBJECT
protected:
    int maxSpeed;
    int actualSpeed;


public:
    Movable(QObject *parent = nullptr, QGraphicsItem* newGraphicItem = nullptr);
    void setActualSpeed(int newSpeed);
    int getMaxSpeed();
signals:

public slots:


};

#endif // MOVABLE_H
