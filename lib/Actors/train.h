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
    Rail* lastRailChecked;
    Rail* occupiedByFirstVehicle;
    bool isIdle;
    bool autopilot;
    int travelDistance;
    bool shunt;

public:
    Train(QObject *parent = nullptr, QGraphicsItem* newGraphicItem = nullptr, Rail* spawnedRail = nullptr);
    Vehicle* getVehicleActor(int indexOfVehicle);
    QGraphicsItem* getVehicleGraphics(int indexOfVehicle);
    QPointF getLocationOnPath(float percentOnPath);
    QVector<Vehicle *> getVehicles() const;
    QVector<Rail *> getRemainingPath() const;
    QVector<Rail *> getTakenPath() const;
    Rail* getActualRail() const;
    Rail* getFirstOccupiedRail();

    bool getDirectionToRailEnd()const;
    bool teleportTrainToRail(Rail* rail, bool direction, bool checkOccupied, int movedByLength);
    bool getShunt();
    const bool getIdle();
    const bool getMoveDirection();
    const bool getAutopilot();

    float getActualPathValue() const;

    int getTrainLength();
    int getRemainToPathEnd();
    int getOnPathLength();

    void actualizeGraphicLocation() override;
    void actualizeGraphicRotation() override;
    void threadedTickEvent() override;
    void tickEvent() override;

    void addMultipleVehicleToTrain(QList<Vehicle*> newVehicles);
    void removeVehicleFromLists(QList<Vehicle *> vehiclesToMove);
    void actualizeMaxSpeed();
    void setActualPathValue(float newValue);
    void setTrainPath(QVector<Rail*> newTrainPath);
    void addNextPartOfPath(QVector<Rail*> addedPartOfPath);
    void recalculateRemainToPathEnd();
    void moveTrain();
    void makePathFromPortal();
    void setActualPathGraphic(Rail *actualRail);
    void actualizeTrainLenth();
    void recalculateSpeed();
    void actualizeOnPathLength();
    void actualizeVehiclesOnPath();
    void selectTrain(bool selected);
    void setdirectionToRailEnd(bool newDirection);
    void changeMoveDirection();
    void idle (bool idleState);
    void setAutopilot(bool newAutopilot);
    void setShunt(bool newShunt);
    void setTravelDistance(int newDistance);

    virtual ~Train();


signals:

public slots:
};

#endif // TRAIN_H
