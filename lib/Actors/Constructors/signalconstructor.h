#ifndef SIGNALCONSTRUCTOR_H
#define SIGNALCONSTRUCTOR_H

#include <Actors/Constructors/railobjectconstructor.h>
#include <QObject>
#include <QGraphicsView>
#include <Actors/rail.h>

class LIB_EXPORT SignalConstructor : public RailobjectConstructor
{
    Q_OBJECT
protected:
    QGraphicsItem* nearestAreaGraphicItem;
    Rail* nearestRail;
    int nearestEndArea;
    const int MAX_SIGNAL_DISTANCE = 120;
public:
    explicit SignalConstructor(QObject *parent = nullptr, QGraphicsItem *newGraphicItem = nullptr, Actor *actorToConstructing = nullptr);
    void actualizeConstructor(QPoint newPoint, int zoomLevel) override;
    void calledCollisionEvent(const QList<Actor *> isInCollision) override; //overrided
    Rail* getNearestRail();
    QGraphicsItem* getNearestAreaGraphic();
    void actorLeaveFromCollision(Actor* actor) override;
    void actorEnterInCollision(Actor* actor) override;
    int getNearestEndArea();
    ~SignalConstructor();
};

#endif // SIGNALCONSTRUCTOR_H
