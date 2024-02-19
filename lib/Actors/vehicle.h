#ifndef VEHICLE_H
#define VEHICLE_H

#include "movable.h"

class LIB_EXPORT Vehicle : public Movable
{
Q_OBJECT
protected:
    int mass; //kg
    int width; //decimeter
    int length; //decimeter
    QPoint firstAxleCenter; //relative
    QPoint secondAxleCenter; //relative
public:
    Vehicle(QObject* parent = nullptr, QGraphicsItem* newGraphicItem = nullptr);
    const int getWidth();
    const int getLegth();
signals:


};

#endif //VEHICLE_H
