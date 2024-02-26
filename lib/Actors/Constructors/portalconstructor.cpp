#include "portalconstructor.h"

PortalConstructor::PortalConstructor(QObject* parent, QGraphicsItem* newGraphicItem, Actor *actorToConstructing)
    : ActorConstructor(parent, newGraphicItem, actorToConstructing)
{
    snappedToRail = false;
    nearestRail = nullptr;
}

void PortalConstructor::calledCollisionEvent(const QList<Actor *> isInCollision)
{
    Actor::calledCollisionEvent(isInCollision); //re-fill actors in collide list and run functions "actorEnterInCollision and actorLeaveFromCollision"
    int testedNearestEndArea = -1;
    int maxDistance = 121;
    Rail* testedNearestRail = nullptr;
    QPoint correctedLocation = location + QPoint(-5,50); //graphics is slided

    //try to find nearest area (end of actual rail)
    for (auto actor : actorsInCollision)
    {
        if (!dynamic_cast<Rail*>(actor)) continue;
        Rail* rail = dynamic_cast<Rail*>(actor);
        QPoint testedPoint1 = rail->getP0WorldLocation().toPoint();
        QPoint testedPoint2 = (rail->getP0WorldLocation() + rail->getP3RelativeLocation()).toPoint();
        int testedDistance1 = getDistance(correctedLocation, testedPoint1);
        int testedDistance2 = getDistance(correctedLocation, testedPoint2);
        if (maxDistance > testedDistance1 && testedDistance1 <= testedDistance2)
        {
            maxDistance = testedDistance1;
            testedNearestEndArea = 0;
            testedNearestRail = rail;
        }
        else if (maxDistance > testedDistance2 && testedDistance2 < testedDistance1)
        {
            maxDistance = testedDistance2;
            testedNearestEndArea = 1;
            testedNearestRail = rail;
        }
    }

    //check nearest conected rails (if rail exist in the same point/area)
    if (testedNearestEndArea != -1 && maxDistance <= 120)
    {
        Rail* retestedRail = nullptr;
        QPoint retestedPoint;
        int testedDistance = 150;
        for (int i = 0; i < 2; i++)
        {
            int conectionValue = i;
            if (testedNearestEndArea == 1) conectionValue +=2;
            if(testedNearestRail->getConnectedRail(conectionValue) != nullptr)
            {
                retestedRail = testedNearestRail->getConnectedRail(conectionValue);
                int newTestedNearestPoint = (retestedRail->getConnection(testedNearestRail)+2)/2-1; //transfer connection point(0-3) to endPoint (0-1)
                retestedPoint = dynamic_cast<QGraphicsPathItem*>(retestedRail->getGraphicItem())->path().pointAtPercent(0.01f).toPoint() + retestedRail->getLocation();
                testedDistance = getDistance(correctedLocation, retestedPoint);
                if (maxDistance > testedDistance)
                {
                    testedNearestRail = retestedRail;
                    testedNearestEndArea = newTestedNearestPoint;
                    maxDistance = testedDistance;
                }
                retestedPoint = dynamic_cast<QGraphicsPathItem*>(retestedRail->getGraphicItem())->path().pointAtPercent(0.99f).toPoint() + retestedRail->getLocation();
                testedDistance = getDistance(correctedLocation, retestedPoint);
                if (maxDistance > testedDistance)
                {
                    testedNearestRail = retestedRail;
                    testedNearestEndArea = newTestedNearestPoint;
                    maxDistance = testedDistance;
                }
            }
        }

        //change location of portal to snap location (nearest end of rail)
        QPoint snapLocation = {-24,-24}; //slide to center
        (testedNearestEndArea == 0) ? snapLocation += testedNearestRail->getLocation() : snapLocation += testedNearestRail->getLocation() + testedNearestRail->getP3RelativeLocation().toPoint();
        snappedToRail = true;
        //setLocation(snapLocation, true);
        setGraphicLocation(snapLocation);
        actualizeGraphicLocation();
    }
    else snappedToRail = false;

    //set visual change (occupied rail)
    if (testedNearestRail != nullptr)
    {
        if (nearestRail != nullptr && testedNearestRail != nearestRail) nearestRail->setOccupied(false,true);
        nearestRail = testedNearestRail;
        nearestRail->setOccupied(true,true);
    }
    else if (nearestRail != nullptr)
    {
        nearestRail->setOccupied(false,true);
        nearestRail = nullptr;
    }
}

void PortalConstructor::actualizeConstructor(QPoint newPoint, int zoomLevel)
{
    if (!snappedToRail)
    {
        QPoint slideLocation = {5,-50};
        setLocation(newPoint + slideLocation, true);
        zoomLevelSaved = zoomLevel;
    }
    else ActorConstructor::actualizeConstructor(newPoint, zoomLevel);

}

Rail* PortalConstructor::getNearestRail()
{
    return nearestRail;
}

PortalConstructor::~PortalConstructor()
{
    for (auto railActor : actorsInCollision)
    {
        Rail* rail = dynamic_cast<Rail*>(railActor);
        rail->setVisibilityOfArea(0, false, nullptr);
        rail->setVisibilityOfArea(1, false, nullptr);
    }
    if (nearestRail != nullptr) nearestRail->setOccupied(false,true);
}
