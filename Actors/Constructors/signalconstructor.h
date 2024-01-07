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
    QList<Rail*> holdedRail;
    QGraphicsItem* nearestArea;
public:
    explicit SignalConstructor(QObject *parent = nullptr, QGraphicsItem *newGraphicItem = nullptr, Actor *actorToConstructing = nullptr);
    void actualizeConstructor(QPoint newPoint) override;
    void actorCollide(const QList<Actor *> actorsInCollision) override; //overrided
    void freeHoldedRail();
    bool holdRail();
    ~SignalConstructor();
};

#endif // SIGNALCONSTRUCTOR_H
