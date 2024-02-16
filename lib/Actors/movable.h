#ifndef MOVABLE_H
#define MOVABLE_H

#include "actor.h"

class LIB_EXPORT Movable : public Actor
{
Q_OBJECT
protected:
    int maxSpeed;
    int actualSpeed;


public:
    Movable(QObject *parent = nullptr, QGraphicsItem* newGraphicItem = nullptr);
    void setActualSpeed(int newSpeed);
    int getMaxSpeed();
    void setMaxSpeed(int newMaxSpeed);

    const int getActualSpeed();

signals:

public slots:


};

#endif // MOVABLE_H
