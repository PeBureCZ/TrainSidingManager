#ifndef RAILSELECTOR_H
#define RAILSELECTOR_H

#include "selectconstructor.h"
#include "Actors/rail.h"
#include <QObject>

class LIB_EXPORT RailSelector : public SelectConstructor
{
    Q_OBJECT
protected:
    Rail* nearestRail;
    int nearestPoint;
    QGraphicsPathItem* visualP1;
    QGraphicsPathItem* visualP2;
public:
    explicit RailSelector(QObject* parent = nullptr, QGraphicsItem* newGraphicItem = nullptr, Actor *actorToConstructing = nullptr);
    QGraphicsPathItem* getP1VisualPoint();
    QGraphicsPathItem *getP2VisualPoint();
    ~RailSelector();
    void calledCollisionEvent(const QList<Actor *> isInCollision) override;
    void actorLeaveFromCollision(Actor *actor) override;
    void actorEnterInCollision(Actor *actor) override;
    void callSelectEvent(QPoint point) override;
    void setUnderSelect(bool newUnderSelect) override;
    void deleteMiddleVisualPoints();
    Actor* getSelectedActor() override;

};

#endif // RAILSELECTOR_H
