#ifndef TRAIN_H
#define TRAIN_H

#include "movable.h"
#include "vehicle.h"
#include "dependencies/trainnavigation.h"
#include "QtMath"

class LIB_EXPORT Train : public Movable
{
Q_OBJECT
protected:
    QGraphicsPathItem* actualPathGraphic;
    Rail* actualRail;
    QVector<Rail*> remainingPath;
    QVector<Rail*> takenPath;
    bool releasePath;
    float onPathValue;
    int onPathLength;  //in decimeters!
    int actualTrainLength; //in decimeters!
    bool directionToRailEnd;
    bool moveForward;
    QVector<Vehicle*> vehicles;
    QVector<QGraphicsItem*> vehicleGraphicsItems;
    int remainToPathEnd;
    float breakLevel;
    float throttleLevel;


public:
    Train(QObject *parent = nullptr, QGraphicsItem* newGraphicItem = nullptr, Rail* spawnedRail = nullptr);
    Vehicle* getVehicleActor(int indexOfVehicle);
    QGraphicsItem* getVehicleGraphics(int indexOfVehicle);
    QPointF getLocationOnPath(float percentOnPath);
    QVector<Vehicle *> getVehicles() const;
    QVector<Rail *> getRemainingPath() const;
    QVector<Rail *> getTakenPath() const;
    Rail* getActualRail() const;
    bool getDirectionToRailEnd()const;
    const bool getMoveDirection();
    float getActualPathValue() const;
    bool teleportTrainToRail(Rail* rail);
    int getTrainLength();
    int getRemainToPathEnd();

    void actualizeGraphicLocation() override;
    void actualizeGraphicRotation() override;
    void threadedTickEvent() override;
    void tickEvent() override;

    void addMultipleVehicleToTrain(QList<Vehicle*> newVehicles);
    void actualizeMaxSpeed();
    void setActualPathValue(float newValue);
    void setTrainPath(QVector<Rail*> newTrainPath);
    void addNextPartOfPath(QVector<Rail*> addedPartOfPath);
    void moveTrain();
    void startAutopilot();
    void setActualPathGraphic(Rail *actualRail);
    void actualizeTrainLenth();
    void recalculateSpeed(int actualDistanceOnRail);
    void actualizeOnPathLength();
    void actualizeVehiclesOnPath();
    void selectTrain(bool selected);

    virtual ~Train();




signals:

public slots:
};

#endif // TRAIN_H
