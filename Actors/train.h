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
    Train(QObject *parent = nullptr, QGraphicsItem* newGraphicItem = nullptr, Rail* spawnedRail = nullptr);
    Vehicle* getVehicleActor(int indexOfVehicle);
    QGraphicsItem* getVehicleGraphics(int indexOfVehicle);
    QPointF getLocationOnPath(float percentOnPath);
    Rail* getActualRail();

    void actualizeGraphicLocation() override;
    float getActualPathValue();
    void addVehicle(Vehicle* newVehicle, QGraphicsItem *graphicsItem);
    void actualizeMaxSpeed();
    void setActualPathValue(float newValue);
    void setTrainPath(QVector<Rail*> newTrainPath);
    void tickEvent() override;
    void moveTrain();
    void startAutopilot();

    virtual ~Train();


signals:

public slots:
};

#endif // TRAIN_H
