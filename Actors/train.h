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
    QVector<Rail*> trainPath;
    float onPathValue;
    int onPathLength; //centimeters!
    bool directionToEnd;
    QVector<Vehicle*> vehicles;
    QVector<QGraphicsItem*> vehicleGraphicsItems;

public:
    virtual ~Train();
    Vehicle* getVehicleActor(int indexOfVehicle);
    QGraphicsItem* getVehicleGraphics(int indexOfVehicle);
    QPointF getLocationOnPath(float percentOnPath);
    Train(QGraphicsItem* newGraphicItem, Rail* spawnedRail);

    float getActualPathValue();

    void addVehicle(Vehicle* newVehicle, QGraphicsItem *graphicsItem);
    void actualizeMaxSpeed();
    void setActualPathValue(float newValue);
    void moveTrain();
    void setTrainPath(QVector<Rail*> newTrainPath);

};

#endif // TRAIN_H
