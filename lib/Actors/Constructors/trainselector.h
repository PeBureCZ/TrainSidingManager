#ifndef TRAINSELECTOR_H
#define TRAINSELECTOR_H

#include "selectconstructor.h"
#include "dependencies/railnavigation.h"
#include <QObject>
#include "Actors/train.h"
#include "Actors/rail.h"

class LIB_EXPORT TrainSelector : public SelectConstructor
{
    Q_OBJECT
protected:
    Train* selectedTrain;
    Signal* nearestSignal;
    Train* nearestTrain;
    Rail* nearestRail;

public:
    explicit TrainSelector(QObject* parent = nullptr, QGraphicsItem* newGraphicItem = nullptr, Actor *actorToConstructing = nullptr);
    void actualizeConstructor(QPoint newPoint, int zoomLevel) override;

    Train *getSelectedTrain();
    void setSelectedTrain();
    Signal* getNearestSignal();
    Train* getNearestTrain();
    void findPathToSignal();
    void findNearestTrain();
    void findNearestSignal();
    void unselectSignal();

    void calledCollisionEvent(const QList<Actor *> isInCollision) override;
    void actorLeaveFromCollision(Actor* actor) override;
    void actorEnterInCollision(Actor* actor) override;

    ~TrainSelector();
};

#endif // TRAINSELECTOR_H
