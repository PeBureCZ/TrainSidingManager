
#ifndef PORTALCONSTRUCTOR_H
#define PORTALCONSTRUCTOR_H

#include "actorconstructor.h"
#include <QObject>
#include "Actors/rail.h"

class PortalConstructor : public ActorConstructor
{
    Q_OBJECT
protected:
    bool snappedToRail;
    Rail* nearestRail;
public:
    PortalConstructor
    (QObject *parent = nullptr,
    QGraphicsItem *newGraphicItem = nullptr,
    Actor *actorToConstructing = nullptr);

    void calledCollisionEvent(const QList<Actor*> isInCollision) override;
    void actualizeConstructor(QPoint newPoint) override;

    ~PortalConstructor();
    Rail* getNearestRail();
};

#endif // PORTALCONSTRUCTOR_H
