#ifndef RAILCONSTRUCTOR_H
#define RAILCONSTRUCTOR_H

#include "actorconstructor.h"
#include "rail.h"

class RailConstructor : public ActorConstructor
{
protected:
    bool startAtSpawnPos; //define if start (percent 0 in percentRange 0-1) is at spawn position (=click pos) or at "tick mouse target" position
    bool lined;
    Rail *connectedRailActor;
    Rail* ownedRail;
    QGraphicsPathItem* ownedPath;

    QPoint P0; //start point
    QPoint P1; //first curve control point
    QPoint P2; //second curve control point
    QPoint P3; //end point

    //FCE - protected
    void setPoints(QPoint endP);

public:
    RailConstructor
    (QGraphicsItem* newGraphicItem = nullptr
    , Actor *actorToConstructing = nullptr
    , QPoint spawnPos = {0,0}
    , Rail* connectedRail = nullptr
    );

    //FCE - public
    QString testFce();
    QPointF getP0Point();
    QPointF getP1Point();
    QPointF getP2Point();
    QPointF getP3Point();
    Rail* getOwnedRail();
    Rail* getConnectedRail();
    void actualizePathVisual();
    void actualizeRail();
    void smoothEndPoint();
    void actualizeConstructor(QPoint newPoint) override;
    ~ RailConstructor();
};

#endif // RAILCONSTRUCTOR_H
