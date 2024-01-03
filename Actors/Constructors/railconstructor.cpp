#include "railconstructor.h"

RailConstructor::RailConstructor
    (QObject* parent, QGraphicsItem* newGraphicItem, Actor *actorToConstructing)
    : ActorConstructor(parent, newGraphicItem, actorToConstructing)
{
    P0 = {0,0};
    P1 = {0,0};
    P2 = {0,0};
    P3 = {0,0};

    ownedRail = nullptr;
    connectedRail = nullptr;
    ownedRail = nullptr;
    ownedPath = nullptr;
    lined = true;
}

void RailConstructor::actualizePathVisual() // NEED REBUILD
{
    ownedPath->setPos(P0.x(),P0.y());
    QPainterPath customPath;
    customPath.cubicTo(P1.x(),P1.y(),P2.x(), P2.y(),P3.x(), P3.y());
    ownedPath->setPath(customPath);
}

void RailConstructor::actualizeRail()
{
    ownedRail->setP0WorldLocation(P0); //ABSOLUTE
    ownedRail->setP1RelativeLocation(P1); //RELATIVE
    ownedRail->setP2RelativeLocation(P2); //RELATIVE
    ownedRail->setP3RelativeLocation(P3); //RELATIVE
}

void RailConstructor::smoothEndPoint()
{
    if (ownedRail != nullptr) ownedRail->smoothP3PointByC1();
}

void RailConstructor::actualizeConstructor(QPoint newPoint)
{
    if (ownedRail != nullptr)
    {
        actualizeRail();
        setPoints(newPoint);
        actualizePathVisual();
        if (ownedRail->getAllTriggers().size() > 0)
        {
            dynamic_cast<Component*>(ownedRail->getAllTriggers()[1])->setRelativeLocation(newPoint - ownedRail->getLocation()); //p3 trigger
        }
    }
    else
    {
        setLocation(newPoint,true);
    }
}

void RailConstructor::setPoints(QPoint endP)
{
    //P0 = WORLD, P1-3 = RELATIVE
    int x = endP.x() - location.x();
    int y = endP.y() - location.y();
    P0 = location; //world
    P3 = {x,y}; //relative

    //set P1 and P2
    if (connectedRail == nullptr)
    {
        P1 = {(x)/2,y/2}; //relative
        P2 = P1; //relative
    }
    else   //Béziere path
    {
        QLineF line(P0, P3+location); //line between P0/P3 (Rail being created by this constructor.)
        QPoint connectedP2world;
        (P0 == connectedRail->getLocation()) ? connectedP2world = connectedRail->getLocation() + connectedRail->getP1RelativeLocation().toPoint()
        : connectedP2world = connectedRail->getLocation() + connectedRail->getP2RelativeLocation().toPoint();

        QLineF lineP2(connectedP2world, P0);
        float reduction = line.length() / lineP2.length();
        if (reduction < 0.05f)  reduction = 0.05f;
        QPoint negativeVector = lineP2.pointAt(1-reduction).toPoint();
        QPoint vectorP2world = (location - (negativeVector - location));
        QPoint vectorP2Local = vectorP2world  - location;

        P1 = vectorP2Local / 2; //relative
        P2 = P1; //relative
    }
}

QPointF RailConstructor::getP0Point()
{
    return {P0};
}

QPointF RailConstructor::getP1Point()
{
    return {P1};
}

QPointF RailConstructor::getP2Point()
{
    return {P2};
}

QPointF RailConstructor::getP3Point()
{
    return {P3};
}

Rail *RailConstructor::getOwnedRail()
{
    return ownedRail; //for return actor call "getActorConstructing()"
}

Rail *RailConstructor::getConnectedRail()
{
    return connectedRail;
}

void RailConstructor::underConstruction(bool constructingNow)
{
    if (constructingNow) graphicItem->setVisible(false);
    else
    {
        setOwnedRail(nullptr);
        setConnectedRail(nullptr);
        graphicItem->setVisible(true);
    }
}

void RailConstructor::setOwnedRail(Rail *newOwnedRail)
{
    ownedRail = newOwnedRail;
    if (newOwnedRail != nullptr)
    {
        ownedPath = dynamic_cast<QGraphicsPathItem*>(ownedRail->getGraphicItem());
        actorConstructing = dynamic_cast<Actor*>(ownedRail);
    }
    else
    {
        ownedPath = nullptr;
        actorConstructing = nullptr;
    }
}

void RailConstructor::setConnectedRail(Rail *newConnectedRail)
{
    connectedRail = newConnectedRail;
}

void RailConstructor::setObjectBoxCollider()
{

    BoxCollider* boxCollider = {};
    for (auto trigger : ownedRail->getAllTriggers())
    {
        if (dynamic_cast<BoxCollider*>(trigger))
        {
            boxCollider = dynamic_cast<BoxCollider*>(trigger);
            break;
        }
    }
    if (boxCollider != nullptr)
    {
        //get and make rotation
        float radian = atan2(static_cast<double>(P3.y()),P3.x());
        float basicRotation = qRadiansToDegrees(radian);
        float correctedRotation = fmod(360 - basicRotation, 360);

        QTransform rotationTransform;
        rotationTransform.rotate(correctedRotation);

        QVector<QPoint> relativeLocations = {};

        //make 10 points on path declare box (still in "rotated" coordinate)
        for (int i = 0; i <= 10; i++)
        {
            float percent = i*0.1f;
            relativeLocations.push_back(ownedPath->path().pointAtPercent(percent).toPoint()); //relative
        }

        //make points "unrotated" to check bounds
        for (auto &point : relativeLocations)
        {
            point = rotationTransform.map(point);
        }

        //make size of box
        int maxX = 0;
        int minX = 0;
        int maxY = 0;
        int minY = 0;
        for (auto point : relativeLocations)
        {
            if (maxX < point.x()) maxX = point.x();
            if (minX > point.x()) minX = point.x();
            if (maxY < point.y()) maxY = point.y();
            if (minY > point.y()) minY = point.y();
        }

        maxX += 40; //decimeters
        minX -= 40; //decimeters
        maxY += 40; //decimeters
        minY -= 40; //decimeters

        QPoint leftUpCorner = {minX, minY};
        QPoint rightDownCorner = {maxX, maxY};

        //set coordination and rotations
        boxCollider->setBoxCollider(leftUpCorner, rightDownCorner, correctedRotation);

    }

}

RailConstructor::~RailConstructor()
{}


