#ifndef TRAIN_H
#define TRAIN_H

#include "movable.h"
#include "rail.h"
#include "vehicle.h"

class Train : public Movable
{
protected:
    QGraphicsPathItem* actualPath;
    Rail* actualRail;
    float onPathValue;
    int onPathLength; //centimeters!
    QVector<Vehicle*> vehicles;
    QVector<QGraphicsItem*> vehicleGraphicsItems;

public:
    Train(QGraphicsItem* newGraphicItem, Rail* spawnedRail);
    virtual ~Train();

    void moveTrain();

    void setActualPathValue(float newValue);
    float getActualPathValue();
    void addVehicle(Vehicle* newVehicle, QGraphicsItem *graphicsItem);
    void actualizeMaxSpeed();

    Vehicle* getVehicleActor(int indexOfVehicle);
    QGraphicsItem* getVehicleGraphics(int indexOfVehicle);
    QPointF getLocationOnPath(float percentOnPath);
};

#endif // TRAIN_H
