#ifndef TRAIN_H
#define TRAIN_H

#include "movable.h"
#include <QGraphicsPathItem>
#include "rail.h"
#include "vehicle.h"

class Train : public Movable
{
protected:
    QGraphicsPathItem* actualPath;
    Rail* actualRail;
    float onPathValue;
    int onPathLength;
    QVector<Vehicle*> vehicles;
    QVector<QGraphicsItem*> vehicleGraphicsItems;

public:
    Train(Rail* spawnedRail);
    virtual ~Train();

    void moveTrain();
    float getActualPathValue();
    void setActualPathValue(float newValue);
    int getActualLengthOnPath();
    void setActualLengthOnPath(int newValue);
    void addVehicle(Vehicle* newVehicle, QGraphicsItem *graphicsItem);
    Vehicle* getVehicleActor(int indexOfVehicle);
    QGraphicsItem* getVehicleGraphics(int indexOfVehicle);
    QPoint getVehicleWorldPos(int indexOfVehicle);
    void setActualPath(QGraphicsPathItem* newPath);
    QGraphicsPathItem* getActualPath();
    QPointF getLocationOnPath(float percentOnPath);
};

#endif // TRAIN_H
