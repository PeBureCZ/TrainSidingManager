#ifndef RAILCONSTRUCTOR_H
#define RAILCONSTRUCTOR_H

#include "actorconstructor.h"
#include <QTransform>
#include "Actors/rail.h"

class RailConstructor : public ActorConstructor
{
Q_OBJECT
protected:
    bool startAtSpawnPos; //define if start (percent 0 in percentRange 0-1) is at spawn position (=click pos) or at "tick mouse target" position
    bool lined;
    Rail *connectedRail;
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
    (QObject* parent = nullptr
    , QGraphicsItem* newGraphicItem = nullptr
    , Actor *actorToConstructing = nullptr
    );

    //FCE - public
    QPointF getP0Point();
    QPointF getP1Point();
    QPointF getP2Point();
    QPointF getP3Point();
    Rail* getOwnedRail();
    Rail* getConnectedRail();
    void underConstruction(bool constructingNow);
    void actualizePathVisual();
    void actualizeRail();
    void smoothEndPoint();
    void actualizeConstructor(QPoint newPoint) override;
    void setObjectBoxCollider() override;
    void setOwnedRail(Rail* newOwnedRail);
    void setConnectedRail(Rail* newConnectedRail);
    ~ RailConstructor();
signals:

public slots:
};

#endif // RAILCONSTRUCTOR_H
