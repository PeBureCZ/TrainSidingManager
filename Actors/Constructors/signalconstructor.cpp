#include "signalconstructor.h"

SignalConstructor::SignalConstructor(QObject* parent, QGraphicsItem* newGraphicItem, Actor *actorToConstructing)
    : RailobjectConstructor(parent, newGraphicItem, actorToConstructing)
{
    holdedRail = nullptr;
}

void SignalConstructor::actualizeConstructor(QPoint newPoint)
{
    QPoint slideLocation = {5,-50};
    setLocation(newPoint + slideLocation, true);
    actualizeGraphicLocation();
}

void SignalConstructor::actorCollide(const QList<Actor*> actorsInCollision)
{
    //overrided function (Actor)
    Rail* nearestRail= nullptr;
    int nearestPoint = -1;

    int distance = 99999999;

    for (auto actor : actorsInCollision)
    {
        if (dynamic_cast<Rail*>(actor))
        {
            Rail* rail = dynamic_cast<Rail*>(actor);

            QPoint testedPoint1 = rail->getP0WorldLocation().toPoint();
            QPoint testedPoint2 = (rail->getP0WorldLocation() + rail->getP3RelativeLocation()).toPoint();
            int testedDistance1 = getDistance(location, testedPoint1);
            int testedDistance2 = getDistance(location, testedPoint2);

            if (distance > testedDistance1 && testedDistance1 <= testedDistance2)
            {
                distance = testedDistance1;
                nearestPoint = 0;
                nearestRail = rail;
            }
            else if (distance > testedDistance2 && testedDistance2 < testedDistance1)
            {
                distance = testedDistance2;
                nearestPoint = 1;
                nearestRail = rail;
            }
        }
    }
    if (nearestRail != holdedRail) freeHoldedRail(); //need rework!
    if (nearestRail != nullptr)
    {   
        holdedRail = nearestRail;
        (nearestPoint == 0) ? nearestRail->setVisibilityOfArea(0, true) : nearestRail->setVisibilityOfArea(0, false);
        (nearestPoint == 1) ? nearestRail->setVisibilityOfArea(1, true) : nearestRail->setVisibilityOfArea(1, false);
    }
}

void SignalConstructor::freeHoldedRail()
{
    if (holdedRail != nullptr)
    {
        holdedRail->setVisibilityOfArea(0, false);
        holdedRail->setVisibilityOfArea(1, false);
        holdedRail = nullptr;
    }
}

bool SignalConstructor::holdRail()
{
    if (holdedRail == nullptr) return false;
    return true;
}

SignalConstructor::~SignalConstructor()
{
    freeHoldedRail();
}


