#ifndef TRAINSELECTOR_H
#define TRAINSELECTOR_H

#include "selectconstructor.h"
#include "dependencies/railnavigation.h"
#include <QObject>
#include "Actors/train.h"
#include "Actors/rail.h"
#include "dependencies/Enums/CustomColors.h"

class LIB_EXPORT TrainSelector : public SelectConstructor
{
    Q_OBJECT
protected:
    Train* selectedTrain;
    Signal* nearestSignal;
    Train* nearestTrain;
    Rail* nearestRail;
    Vehicle* nearestVehicle;
private:
    int getSlateFromSprite(int state);

public:
    explicit TrainSelector(QObject* parent = nullptr, QGraphicsItem* newGraphicItem = nullptr, Actor *actorToConstructing = nullptr);
    void actualizeConstructor(QPoint newPoint, int zoomLevel) override;

    Signal* getNearestSignal();
    Train* getNearestTrain();
    Train *getSelectedTrain();
    Vehicle* getNearestVehicle();

    void setSelectedTrain();
    void findPathToSignal();
    void findNearestVehicle();
    void findNearestSignal();
    void unselectSignal();

    void calledCollisionEvent(const QList<Actor *> isInCollision) override;
    void actorLeaveFromCollision(Actor* actor) override;
    void actorEnterInCollision(Actor* actor) override;

    ~TrainSelector();
};

#endif // TRAINSELECTOR_H
