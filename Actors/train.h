#ifndef TRAIN_H
#define TRAIN_H

#include "movable.h"
#include "vehicle.h"
#include "dependencies/trainnavigation.h"

class Train : public Movable
{
Q_OBJECT
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
    Train(QObject *parent = nullptr, QGraphicsItem* newGraphicItem = nullptr, Rail* spawnedRail = nullptr);
    Rail* getActualRail();

    float getActualPathValue();

    void addVehicle(Vehicle* newVehicle, QGraphicsItem *graphicsItem);
    void actualizeMaxSpeed();
    void setActualPathValue(float newValue);
    void moveTrain();
    void setTrainPath(QVector<Rail*> newTrainPath);
    void tickEvent() override;
signals:

public slots:
};

#endif // TRAIN_H
