#ifndef SIGNALCONSTRUCTOR_H
#define SIGNALCONSTRUCTOR_H

#include <Actors/Constructors/railobjectconstructor.h>
#include <QObject>
#include <QGraphicsView>
#include <Actors/rail.h>

class SignalConstructor : public RailobjectConstructor
{
    Q_OBJECT
protected:
    QGraphicsItem* nearestArea;
public:
    explicit SignalConstructor(QObject *parent = nullptr, QGraphicsItem *newGraphicItem = nullptr, Actor *actorToConstructing = nullptr);
    void actualizeConstructor(QPoint newPoint) override;
    void actorCollide(const QList<Actor *> isInCollision) override; //overrided
    void freeHoldedRail();
    bool holdRail();
    void actorLeaveFromCollision(Actor* actor) override;
    void actorEnterInCollision(Actor* actor) override;
    ~SignalConstructor();
};

#endif // SIGNALCONSTRUCTOR_H
