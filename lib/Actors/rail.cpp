#include "rail.h"

Rail::Rail(QObject* parent, QGraphicsItem* newGraphicItem) : RailwayObject(parent, newGraphicItem)
{
    P0 = {0,0};
    P1 = {0,0};
    P2 = {0,0};
    P3 = {0,0};
    conectionA0 = nullptr; //connection 0
    conectionB0 = nullptr; //connection 1
    conectionC1 = nullptr; //connection 2
    conectionD1 = nullptr; //connection 3
    lined = true;
    startArea = nullptr;
    endArea = nullptr;
    occupied = false;
    occupiedBy = {};
    visuallyOccupied = false;
    signalP0 = nullptr;
    signalP3 = nullptr;
    shuntAllowed = true;
}

QPointF Rail::getP0WorldLocation()
{
    return P0;
}

QPointF Rail::getP1RelativeLocation()
{
    return P1;
}

QPointF Rail::getP2RelativeLocation()
{
    return P2;
}

QPointF Rail::getP3RelativeLocation()
{
    return P3;
}

Rail *Rail:: getConnectedRail(const int connection)
{
    switch (connection)
    {
        case 0:
        {
            return conectionA0;
            break;
        }
        case 1:
        {
            return conectionB0;
            break;
        }
        case 2:
        {
            return conectionC1;
            break;
        }
        case 3:
        {
            return conectionD1;
        }
    }
}

QGraphicsItem *Rail::getAreaGraphic(const int area)
{
        if (area == 0) return startArea;
        else if (area == 1) return endArea;
        else return nullptr;
}

void Rail::setConnectedRail(Rail* connectedRail, const int connection)
{
    switch (connection)
    {
        case 0:
        {
            conectionA0 = connectedRail;
            break;
        }
        case 1:
        {
            conectionB0 = connectedRail;
            break;
        }
        case 2:
        {
            conectionC1 = connectedRail;
            break;
        }
        case 3:
        {
            conectionD1 = connectedRail;
        }
    }
}

void Rail::setP0WorldLocation(const QPoint newPoint)
{
    P0 = newPoint;
}

void Rail::setP1RelativeLocation(const QPoint newPoint)
{
    P1 = newPoint;
}

void Rail::setP2RelativeLocation(const QPoint newPoint)
{
    P2 = newPoint;
}

void Rail::setP3RelativeLocation(const QPoint newPoint)
{
    P3 = newPoint;
}

void Rail::setLined(const bool newBool)
{
    lined = newBool;
}

void Rail::createArea(const int area, QGraphicsItem *graphicItem)
{
    if (area == 0 && startArea != nullptr) deleteArea(0);
    else if (area == 1 && endArea != nullptr) deleteArea(1);
    if (area == 0) startArea = graphicItem;
    else if (area == 1) endArea = graphicItem;
}

void Rail::deleteArea(const int area)
{
    if (area == 0 && startArea != nullptr)
    {
        delete startArea;
        startArea = nullptr;
        return;
    }
    if (area == 1 && endArea != nullptr)
    {
        delete endArea;
        endArea = nullptr;
    }
}

void Rail::setVisibilityOfArea(const int area, const bool visible, QColor color)
{
    QGraphicsItem* changedGraphic = nullptr;
    if (area == 0) changedGraphic = startArea;
    else if (area == 1) changedGraphic = endArea;
    if (visible)
    {
        QPen newPen;
        (color != nullptr) ? newPen.setColor(color) : newPen.setColor(Qt::red);

        if (changedGraphic != nullptr)
        {
            if (color != nullptr)
            {
                if (color == Qt::green)
                {
                    changedGraphic->setZValue(4);
                    newPen.setWidth(8);
                }
                else
                {
                    changedGraphic->setZValue(0);
                    newPen.setWidth(3);
                }
                dynamic_cast<QGraphicsPathItem*>(changedGraphic)->setPen(newPen);
            }
        }
    }
    if (changedGraphic != nullptr) changedGraphic->setVisible(visible);
}

void Rail::actualizeAreasPosition()
{
    QPoint reduction = {VISUAL_AREA_SIZE/2,VISUAL_AREA_SIZE/2};
    if (startArea != nullptr) startArea->setPos((P0 - reduction).toPointF());
    if (endArea != nullptr) endArea->setPos((P0+P3-reduction).toPointF());
}

void Rail::connectRails(Rail *connectedRail, const bool connectedAtStart) //connectedRail have to be always created by constructor
{
    //conect rail function always conect P3 point from constructor
    QPoint connectedRailP3 = connectedRail->getLocation() + connectedRail->getP3RelativeLocation().toPoint(); //world coordinate
    QPoint connectedRailP0 = connectedRail->getLocation(); //world coordinate
    QLineF distanceOne(connectedRailP0, P0);
    QLineF distanceTwo(connectedRailP3, P0);
    if (connectedAtStart) //connect at start = connect this rail at P0 to connectedRail
    {
        if (distanceOne.length() < distanceTwo.length()) //true --> need connect this(P0) & connectedRail(P0)
        {
            if (conectionA0 == nullptr)
            {
                if (connectedRail->getConnectedRail(0) == nullptr)
                {
                    setConnectedRail(connectedRail, 0);
                    connectedRail->setConnectedRail(dynamic_cast<Rail*>(this), 0);
                }
                else if (connectedRail->getConnectedRail(1) == nullptr)
                {
                    setConnectedRail(connectedRail, 0);
                    connectedRail->setConnectedRail(dynamic_cast<Rail*>(this), 1);
                }
            }
            else if (conectionB0 == nullptr)
            {
                if (connectedRail->getConnectedRail(0) == nullptr)
                {
                    setConnectedRail(connectedRail, 1);
                    connectedRail->setConnectedRail(dynamic_cast<Rail*>(this), 0);
                }
                else if (connectedRail->getConnectedRail(1) == nullptr)
                {
                    setConnectedRail(connectedRail, 1);
                    connectedRail->setConnectedRail(dynamic_cast<Rail*>(this), 1);
                }
            }
            else {} //cant connect...not yet
        }
        else //need connect this(P0) & connectedRail(P3)
        {
            if (conectionA0== nullptr)
            {
                if (connectedRail->getConnectedRail(2) == nullptr)
                {
                    setConnectedRail(connectedRail, 0);
                    connectedRail->setConnectedRail(dynamic_cast<Rail*>(this), 2);
                }
                else if (connectedRail->getConnectedRail(3) == nullptr)
                {
                    setConnectedRail(connectedRail, 0);
                    connectedRail->setConnectedRail(dynamic_cast<Rail*>(this), 3);
                }
            }
            else if (conectionB0 == nullptr)
            {
                if (connectedRail->getConnectedRail(2) == nullptr)
                {
                    setConnectedRail(connectedRail, 1);
                    connectedRail->setConnectedRail(dynamic_cast<Rail*>(this), 2);
                }
                else if (connectedRail->getConnectedRail(3) == nullptr)
                {
                    setConnectedRail(connectedRail, 1);
                    connectedRail->setConnectedRail(dynamic_cast<Rail*>(this), 3);
                }
            }
            else {} //cant connect...not yet
        }
    }
    else //connect at end = connect this rail at P3 to connectedRail
    {
        QLineF distanceOne(connectedRailP0, getLocation() + P3);
        QLineF distanceTwo(connectedRailP3, getLocation() + P3);
        if (distanceOne.length() < distanceTwo.length()) //true --> need connect this(P3) & connectedRail(P0)
        {
            if (conectionC1 == nullptr)
            {
                if (connectedRail->getConnectedRail(0) == nullptr)
                {
                    setConnectedRail(connectedRail, 2);
                    connectedRail->setConnectedRail(dynamic_cast<Rail*>(this), 0);
                }
                else if (connectedRail->getConnectedRail(1) == nullptr)
                {
                    setConnectedRail(connectedRail, 2);
                    connectedRail->setConnectedRail(dynamic_cast<Rail*>(this), 1);
                }
            }
            else if (conectionD1 == nullptr)
            {
                if (connectedRail->getConnectedRail(0) == nullptr)
                {
                    setConnectedRail(connectedRail, 3);
                    connectedRail->setConnectedRail(dynamic_cast<Rail*>(this), 0);
                }
                else if (connectedRail->getConnectedRail(1) == nullptr)
                {
                    setConnectedRail(connectedRail, 3);
                    connectedRail->setConnectedRail(dynamic_cast<Rail*>(this),1);
                }
            }
            else {} //cant connect...not yet
        }
        else //need connect this(P3) & connectedRail(P3)
        {
            if (conectionC1 == nullptr)
            {
                if (connectedRail->getConnectedRail(2) == nullptr)
                {
                    setConnectedRail(connectedRail, 2);
                    connectedRail->setConnectedRail(dynamic_cast<Rail*>(this), 2);
                }
                else if (connectedRail->getConnectedRail(3) == nullptr)
                {
                    setConnectedRail(connectedRail, 2);
                    connectedRail->setConnectedRail(dynamic_cast<Rail*>(this), 3);
                }
            }
            else if (conectionD1 == nullptr)
            {
                if (connectedRail->getConnectedRail(2) == nullptr)
                {
                    setConnectedRail(connectedRail, 3);
                    connectedRail->setConnectedRail(dynamic_cast<Rail*>(this), 2);
                }
                else if (connectedRail->getConnectedRail(3) == nullptr)
                {
                    setConnectedRail(connectedRail, 3);
                    connectedRail->setConnectedRail(dynamic_cast<Rail*>(this), 3);
                }
            }
            else {} //cant connect...not yet
        }
    }
}

void Rail::unconnectRail(Rail *unconnectedRail)
{
    if (conectionA0 == unconnectedRail) conectionA0 = {};
    if (conectionB0 == unconnectedRail) conectionB0 = {};
    if (conectionC1 == unconnectedRail) conectionC1 = {};
    if (conectionD1 == unconnectedRail) conectionD1 = {};
}

void Rail::smoothConnectionC1(bool changeP2Distance)
{
    lined = false;
    QPoint negativeVectorP2 = {999999,999999};
    QPoint mirrorCenterPoint;

    //always smooth only A0 or C1 (B & D is always conection smoothed like A or C)
    if (conectionC1 != nullptr)
    {
        if (conectionC1->getConnection(this) == 0 || conectionC1->getConnection(this) == 1)
        {
            mirrorCenterPoint = conectionC1->getLocation();
            negativeVectorP2 = conectionC1->getLocation() + conectionC1->getP1RelativeLocation().toPoint();
        }
        else if (conectionC1->getConnection(this) == 2 || conectionC1->getConnection(this) == 3) //this(P3) is connected to P3(connected)
        {
            negativeVectorP2 = conectionC1->getLocation() + conectionC1->getP2RelativeLocation().toPoint();
            mirrorCenterPoint = conectionC1->getLocation() + conectionC1->getP3RelativeLocation().toPoint();
        }
    }
    if (negativeVectorP2 != QPoint(999999,999999))
    {
        if (changeP2Distance) P2 = (2*mirrorCenterPoint) - negativeVectorP2  - P0;
        else
        {
            QPoint oldP2World= P0+P2;
            int oldInterpolationDistance = getDistance(mirrorCenterPoint,oldP2World);  //původní vzdálenost od P1
            QPoint newP2 = (2*mirrorCenterPoint) - negativeVectorP2;
            int newInterpolationDistance = getDistance(mirrorCenterPoint,newP2);  //nová vzdálenost od P1
            float interpolationFactor = static_cast<float>(oldInterpolationDistance) / static_cast<float>(newInterpolationDistance);

            //correction in big differences to minimal / maximal values
            if (interpolationFactor > 5.0) interpolationFactor = 5.0;
            if (interpolationFactor < 0.2) interpolationFactor = 0.2;

            int x = static_cast<float>(mirrorCenterPoint.x()) + interpolationFactor * (static_cast<float>(newP2.x()) - static_cast<float>(mirrorCenterPoint.x()));
            int y = static_cast<float>(mirrorCenterPoint.y()) + interpolationFactor * (static_cast<float>(newP2.y()) - static_cast<float>(mirrorCenterPoint.y()));
            QPoint shortedP2 = QPoint(x,y);  //A + t * (B - A);
            P2 = shortedP2 - P0;
        }
        P3 = mirrorCenterPoint - P0;
    }
    moveRailPoints(P0,P1,P2,P3);
}

void Rail::smoothConnectionA0(bool changeP1Distance)
{
    lined = false;
    QPoint negativeVectorP1 = {999999, 999999};
    int negativeVectorDistance = 0;
    QPoint mirrorCenterPoint;

    //always smooth only A0 or C1 (B & D is always conection smoothed like A or C)
    if (conectionA0 != nullptr)
    {
        if (conectionA0->getConnection(this) == 0 || conectionA0->getConnection(this) == 1)
        {
            negativeVectorP1 = conectionA0->getLocation() + conectionA0->getP1RelativeLocation().toPoint();
            mirrorCenterPoint = conectionA0->getLocation();

        }
        else if (conectionA0->getConnection(this) == 2 || conectionA0->getConnection(this) == 3)//this (P0) is connected to P3(connected)
        {
            mirrorCenterPoint = conectionA0->getLocation() + conectionA0->getP3RelativeLocation().toPoint();
            negativeVectorP1 = conectionA0->getLocation() + conectionA0->getP2RelativeLocation().toPoint();
        }
        negativeVectorDistance = getDistance(negativeVectorP1, mirrorCenterPoint);
    }

    if (negativeVectorP1 != QPoint(999999,999999))
    {
        QPoint oldP3World = P0+P3;
        QPoint oldP2World= P0+P2;
        if (changeP1Distance)
        { 
            P1 = (2*mirrorCenterPoint) - negativeVectorP1 - P0;
        }
        else
        {
            QPoint oldP1World= P0+P1;
            int oldInterpolationDistance = getDistance(mirrorCenterPoint,oldP1World);  //původní vzdálenost od P1
            QPoint newP1 = (2*mirrorCenterPoint) - negativeVectorP1;
            int newInterpolationDistance = getDistance(mirrorCenterPoint,newP1);  //nová vzdálenost od P1
            float interpolationFactor = static_cast<float>(oldInterpolationDistance) / static_cast<float>(newInterpolationDistance);

            //correction in big differences to minimal / maximal values
            if (interpolationFactor > 5.0) interpolationFactor = 5.0;
            if (interpolationFactor < 0.2) interpolationFactor = 0.2;

            int x = static_cast<float>(mirrorCenterPoint.x()) + interpolationFactor * (static_cast<float>(newP1.x()) - static_cast<float>(mirrorCenterPoint.x()));
            int y = static_cast<float>(mirrorCenterPoint.y()) + interpolationFactor * (static_cast<float>(newP1.y()) - static_cast<float>(mirrorCenterPoint.y()));
            QPoint shortedP1 = QPoint(x,y);  //A + t * (B - A);
            P1 = shortedP1 - P0;


        }
        P0 = mirrorCenterPoint; //position is not actualized yet
        P2 = oldP2World - P0;
        P3 = oldP3World - P0;
    }
    moveRailPoints(P0,P1,P2,P3);
}

bool Rail::getLined()
{
    return lined;
}

bool Rail::getOccupied()
{
    return occupied;
}

bool Rail::getShuntAllowed()
{
    return shuntAllowed;
}

void Rail::setOccupied(const bool isOccupied, Actor* actor )
{
    using namespace customQColors;
    if (isOccupied) occupiedBy.push_back(actor);
    else
    {
        int index = occupiedBy.indexOf(actor);
        if (index != -1) occupiedBy.removeAt(index);
    }

    if (occupiedBy.size() > 0 && isOccupied)
    {
        occupied = isOccupied;
        setRailColor(SELECTED_RAIL_COLOR, SELECTED_RAIL_LAYER);
    }
    else if (occupiedBy.size() > 0 && !isOccupied) setRailColor(OCCUPIED_RAIL_COLOR, SELECTED_RAIL_LAYER);
    else
    {
        setRailColor(DEFAULT_RAIL_COLOR, UNSELECTED_RAIL_LAYER);
        occupied = isOccupied;
    }
}

void Rail::setRailColor(QColor color, int layerEnum)
{
    using namespace customQColors;
    QGraphicsPathItem* graphicPath = dynamic_cast<QGraphicsPathItem*>(graphicItem);
    QPen newPen = graphicPath->pen();
    newPen.setColor(color);
    graphicPath->setPen(newPen);
    graphicPath->setZValue(layerEnum);
}

void Rail::moveRailPoints(QPoint newP0, QPoint newP1, QPoint newP2, QPoint newP3)
{
    setLocation(newP0, true);
    setP0WorldLocation(newP0);
    setP1RelativeLocation(newP1);
    setP2RelativeLocation(newP2);
    setP3RelativeLocation(newP3);
    actualizeAreasPosition();

    QPainterPath newPath;
    newPath.cubicTo(newP1.x(),newP1.y(),newP2.x(), newP2.y(),newP3.x(), newP3.y());
    dynamic_cast<QGraphicsPathItem*>(getGraphicItem())->setPath(newPath);

    getP3Trigger()->setRelativeLocation(newP3);
    getP0Trigger()->setRelativeLocation(newP0);

    setRailObjectBoxCollider();
}

void Rail::setRailObjectBoxCollider()
{
    BoxCollider* boxCollider = {};
    for (auto trigger : getTriggers())
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
        float correctedRotation = fmod(360+90 - basicRotation, 360);

        QTransform rotationTransform;
        rotationTransform.rotate(correctedRotation);

        //boxCollider->setRelativeRotation(correctedRotation);
        QVector<QPoint> relativeLocations = {};

        //make 10 points on path declare box (still in "rotated" coordinate)
        for (int i = 0; i <= 10; i++)
        {
            float percent = i*0.1f;
            relativeLocations.push_back(dynamic_cast<QGraphicsPathItem*>(graphicItem)->path().pointAtPercent(percent).toPoint()); //relative
        }

        //make points "unrotated" to set bounds
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

        QPoint leftUpCorner = {minX-80,-80};
        QPoint rightDownCorner = {maxX+80, maxY+80};
        boxCollider->setRelativeLocation(QPoint(0,maxY/2));

        //set coordination and rotations
        boxCollider->setBoxCollider(leftUpCorner, rightDownCorner, correctedRotation);
    }
}

void Rail::addSignal(int numberOfEndPoint, Signal* signalActor)
{
    if (numberOfEndPoint == 0) signalP0 = signalActor;
    else if (numberOfEndPoint == 1) signalP3 = signalActor;
}

void Rail::actorLeaveFromCollision(Actor *actor)
{
    //RELEASE SIGNAL (used if the signal was deleted before the rail. A Signal can´t include Rail!)
    if (dynamic_cast<Signal*>(actor))
    {
        Signal* removedSignal = dynamic_cast<Signal*>(actor);
        if (signalP0 == removedSignal) signalP0 = nullptr;
        else if (signalP3 == removedSignal) signalP3 = nullptr;
    }
}

Signal *Rail::getSignal(int numberOfEndPoint) const
{
    if (numberOfEndPoint == 0) return signalP0;
    else if (numberOfEndPoint == 1) return signalP3;
    return nullptr;
}

QList<Actor*> Rail::getOccupiedBy()
{
    return occupiedBy;
}

Trigger *Rail::getP0Trigger()
{
    QList<Trigger*> allTriggers = getTriggers();
    if (allTriggers.size() > 0) return allTriggers[0];
    return nullptr;
}

Trigger* Rail::getP3Trigger()
{
    QList<Trigger*> allTriggers = getTriggers();
    if (allTriggers.size() > 1) return allTriggers[1];
    return nullptr;
}

int Rail::getLengthOfRail() const
{
    return static_cast<int>(dynamic_cast<QGraphicsPathItem*>(graphicItem)->path().length());
}

int Rail::getConnection(const Rail *rail) const
{
    if (conectionA0 == rail) return 0; //connection 0
    if (conectionB0 == rail) return 1; //connection 1
    if (conectionC1 == rail) return 2; //connection 2
    if (conectionD1 == rail) return 3; //connection 3
    return -1;
}

int Rail::getVisualAreaSize()
{
    return VISUAL_AREA_SIZE;
}

Rail::~Rail()
{
    if (conectionA0 != nullptr) conectionA0->unconnectRail(dynamic_cast<Rail*>(this));
    if (conectionB0 != nullptr) conectionB0->unconnectRail(dynamic_cast<Rail*>(this));
    if (conectionC1 != nullptr) conectionC1->unconnectRail(dynamic_cast<Rail*>(this));
    if (conectionD1 != nullptr) conectionD1->unconnectRail(dynamic_cast<Rail*>(this));
    deleteArea(0);
    deleteArea(1);
}

