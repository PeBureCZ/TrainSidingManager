#ifndef TRAIN_H
#define TRAIN_H

#include "movable.h"
#include "vehicle.h"
#include "dependencies/trainnavigation.h"

class LIB_EXPORT Train : public Movable
{
Q_OBJECT
protected:
    QGraphicsPathItem* actualPathGraphic;
    Rail* actualRail;
    QVector<Rail*> trainPath;
    float onPathValue;
    int onPathLength;  //in decimeters!
    int actualTrainLength; //in decimeters!
    bool directionToRailEnd;
    bool moveForward;
    QVector<Vehicle*> vehicles;
    QVector<QGraphicsItem*> vehicleGraphicsItems;


public:
    Train(QObject *parent = nullptr, QGraphicsItem* newGraphicItem = nullptr, Rail* spawnedRail = nullptr);
    Vehicle* getVehicleActor(int indexOfVehicle);
    QGraphicsItem* getVehicleGraphics(int indexOfVehicle);
    QPointF getLocationOnPath(float percentOnPath);
    QVector<Vehicle *> getVehicles() const;
    QVector<Rail *> getTrainPath() const;
    Rail* getActualRail() const;
    bool getDirectionToRailEnd()const;
    const bool getMoveDirection();
    float getActualPathValue() const;

    void actualizeGraphicLocation() override;
    void tickEvent() override;

    void addMultipleVehicleToTrain(QList<Vehicle*> newVehicles);
    void actualizeMaxSpeed();
    void setActualPathValue(float newValue);
    void setTrainPath(QVector<Rail*> newTrainPath); 
    void moveTrain();
    void startAutopilot();
    void setActualPathGraphic(Rail *actualRail);
    void teleportTrainToRail(Rail* rail);
    void actualizeTrainLenth();
    void recalculateSpeed(int actualDistanceOnRail);

    virtual ~Train();




signals:

public slots:
};

#endif // TRAIN_H
