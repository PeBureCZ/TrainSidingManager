#ifndef VEHICLE_H
#define VEHICLE_H

#include "movable.h"

class Vehicle : public Movable
{
Q_OBJECT
protected:
    int mass; //kg
    int width; //decimeter
    int length; //decimeter
    QPoint firstAxleCenter; //relative
    int secondAxleDistance; //relative
public:
    Vehicle(QObject* parent = nullptr, QGraphicsItem* newGraphicItem = nullptr);
    QPoint axlePos();
signals:

public slots:
};

#endif //VEHICLE_H
