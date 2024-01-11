#ifndef RAILSELECTOR_H
#define RAILSELECTOR_H

#include "selectconstructor.h"
#include "Actors/rail.h"
#include <QObject>

class RailSelector : public SelectConstructor
{
    Q_OBJECT
protected:
    Rail* nearestRail;
    int nearestPoint;
public:
    explicit RailSelector(QObject* parent = nullptr, QGraphicsItem* newGraphicItem = nullptr, Actor *actorToConstructing = nullptr);
    ~RailSelector();
    void calledCollisionEvent(const QList<Actor *> isInCollision) override;
    void actorLeaveFromCollision(Actor *actor) override;
    void actorEnterInCollision(Actor *actor) override;
    void callSelectEvent(QPoint point) override;
};

#endif // RAILSELECTOR_H
