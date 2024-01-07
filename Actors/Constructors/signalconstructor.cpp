#include "signalconstructor.h"

SignalConstructor::SignalConstructor(QObject* parent, QGraphicsItem* newGraphicItem, Actor *actorToConstructing)
    : RailobjectConstructor(parent, newGraphicItem, actorToConstructing)
{
    holdedRail = {};
    nearestArea = nullptr;
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
    Rail* nearestRail = nullptr;
    int nearestPoint = -1;

    int distance = 120;

    for (auto rail : holdedRail) //hidde no longer collided rails
    {
        int index = actorsInCollision.indexOf(rail);
        if (index == -1) //rail is no longer in actorsInCollision QList
        {
            rail->setVisibilityOfArea(0, false, nullptr);
            rail->setVisibilityOfArea(1, false, nullptr);
            holdedRail.removeOne(rail);
        }
    }

    for (auto actor : actorsInCollision) //show newly collided rail
    {
        if (dynamic_cast<Rail*>(actor))
        {        
            Rail* rail = dynamic_cast<Rail*>(actor);
            int index = holdedRail.indexOf(rail);
            if (index == -1) //actor->rail is not in holdedRail QList -> need add
            {
                holdedRail.push_back(rail);
                rail->setVisibilityOfArea(0, true, Qt::red);
                rail->setVisibilityOfArea(1, true, Qt::red);
            }

            //try to find nearest area (end of rail)
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
    if (nearestRail != nullptr)
    {
        QGraphicsItem* areaItem = nearestRail->getAreaGraphic(nearestPoint);
        if (areaItem != nullptr && areaItem != nearestArea)
        {
            QPen newPen(Qt::red);
            (nearestPoint == -1) ? newPen.setWidth(3) : newPen.setWidth(8);
            if (nearestArea != nullptr) dynamic_cast<QGraphicsPathItem*>(nearestArea)->setPen(newPen);
            nearestArea = areaItem;
        }
        if (nearestPoint == 0)
        {
            nearestRail->setVisibilityOfArea(0, true, Qt::green);
            nearestArea->setZValue(0);
        }
        else if (nearestPoint == 1)
        {
            nearestRail->setVisibilityOfArea(1, true, Qt::green);
            nearestArea->setZValue(0);
        }
    }
    else if (nearestArea != nullptr)
    {
        QPen newPen(Qt::red);
        newPen.setWidth(3);
        dynamic_cast<QGraphicsPathItem*>(nearestArea)->setPen(newPen);
        nearestArea->setZValue(2);
        nearestArea = nullptr;

    }

}

void SignalConstructor::freeHoldedRail()
{
    for (auto rail : holdedRail)
    {
        rail->setVisibilityOfArea(0, false, nullptr);
        rail->setVisibilityOfArea(1, false, nullptr);
    }
    holdedRail.clear();
    nearestArea = nullptr;
}

bool SignalConstructor::holdRail()
{
    if (nearestArea != nullptr) return true;
    return false;
}

SignalConstructor::~SignalConstructor()
{
    freeHoldedRail();
}


