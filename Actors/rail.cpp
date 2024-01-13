#include "rail.h"

Rail::Rail(QObject* parent, QGraphicsItem* newGraphicItem) : RailwayObject(parent, newGraphicItem)
{
    P0 = {0,0};
    P1 = {0,0};
    P2 = {0,0};
    P3 = {0,0};
    conectionA0 = {}; //connection 0
    conectionB0 = {}; //connection 1
    conectionC1 = {}; //connection 2
    conectionD1 = {}; //connection 3
    lined = true;
    startArea = nullptr;
    endArea = nullptr;
    occupied = false;
    visuallyOccupied = false;
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

Rail *Rail::getConnectedRail(const int connection)
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

void Rail::unconnectRails(Rail *unconnectedRail)
{
    if (conectionA0 == unconnectedRail) conectionA0 = {};
    if (conectionB0 == unconnectedRail) conectionB0 = {};
    if (conectionC1 == unconnectedRail) conectionC1 = {};
    if (conectionD1 == unconnectedRail) conectionD1 = {};
}

void Rail::smoothConnectionC1()
{
    lined = false;
    QPoint negativeVectorP2 = {999999,999999};
    QPoint interpolationP2;

    //always smooth only A0 or C1 (B & D) is always conection

    if (conectionC1 != nullptr)
    {
        if (conectionC1->getConnection(this) == 0 || conectionC1->getConnection(this) == 1)
        {
            interpolationP2 = conectionC1->getLocation();
            negativeVectorP2 = conectionC1->getLocation() + conectionC1->getP1RelativeLocation().toPoint();
        }
        else if (conectionC1->getConnection(this) == 2 || conectionC1->getConnection(this) == 3) //this(P3) is connected to P3(connected)
        {
            negativeVectorP2 = conectionC1->getLocation() + conectionC1->getP2RelativeLocation().toPoint();
            interpolationP2 = conectionC1->getLocation() + conectionC1->getP3RelativeLocation().toPoint();
        }
    }

    QPainterPath smoothPath;
    if (negativeVectorP2 != QPoint(999999,999999))
    {
        P2 = (2*interpolationP2) - negativeVectorP2  - P0;
        P3 = interpolationP2 - P0;
    }

    smoothPath.cubicTo(P1.x(),P1.y(),P2.x(), P2.y(),P3.x(), P3.y());
    dynamic_cast<QGraphicsPathItem*>(graphicItem)->setPath(smoothPath);

    dynamic_cast<QGraphicsPathItem*>(graphicItem)->setPos(P0);

}

void Rail::smoothConnectionA0()
{
    lined = false;
    QPoint negativeVectorP1 = {999999, 999999};
    QPoint interpolationP1;

    //always smooth only A0 or C1 (B & D) is always conection
    if (conectionA0 != nullptr)
    {
        if (conectionA0->getConnection(this) == 0 || conectionA0->getConnection(this) == 1)
        {
            negativeVectorP1 = conectionA0->getLocation() + conectionA0->getP1RelativeLocation().toPoint();
            interpolationP1 = conectionA0->getLocation();
        }
        else if (conectionA0->getConnection(this) == 2 || conectionA0->getConnection(this) == 3)//this (P0) is connected to P3(connected)
        {
            interpolationP1 = conectionA0->getLocation() + conectionA0->getP3RelativeLocation().toPoint();
            negativeVectorP1 = conectionA0->getLocation() + conectionA0->getP2RelativeLocation().toPoint();
        }
    }

    QPoint oldP3World = P0+P3;
    QPainterPath smoothPath;
    if (negativeVectorP1 != QPoint(999999,999999))
    {
        P0 = interpolationP1; //position is not actualized yet
        P1 = (2*interpolationP1) - negativeVectorP1 - P0;
        P3 = oldP3World-P0;
    }
    smoothPath.cubicTo(P1.x(),P1.y(),P2.x(), P2.y(),P3.x(), P3.y());
    dynamic_cast<QGraphicsPathItem*>(graphicItem)->setPath(smoothPath);
    dynamic_cast<QGraphicsPathItem*>(graphicItem)->setPos(P0);
}

bool Rail::getLined()
{
    return lined;
}

bool Rail::getOccupied()
{
    return occupied;
}

void Rail::setOccupied(const bool newOccupied, bool setVisualToOccupied)
{
    occupied = newOccupied;
    if (setVisualToOccupied) setVisualOccupied(newOccupied);
}

void Rail::setVisualOccupied(const bool newsVisualState)
{
    visuallyOccupied = newsVisualState;
    if (newsVisualState)
    {
        //change visual to new = true
        QGraphicsPathItem* graphicPath = dynamic_cast<QGraphicsPathItem*>(graphicItem);
        QPen newPen = graphicPath->pen();
        newPen.setColor(QColor(0,255,255,255));
        graphicPath->setPen(newPen);
    }
    else
    {
        QGraphicsPathItem* graphicPath = dynamic_cast<QGraphicsPathItem*>(graphicItem);
        QPen newPen = graphicPath->pen();
        newPen.setColor(Qt::blue);
        graphicPath->setPen(newPen);
    }
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
}

void Rail::setObjectBoxCollider()
{
    BoxCollider* boxCollider = {};
    for (auto trigger : getAllTriggers())
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
            relativeLocations.push_back(dynamic_cast<QGraphicsPathItem*>(graphicItem)->path().pointAtPercent(percent).toPoint()); //relative
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

Trigger *Rail::getP0Trigger()
{
    QList<Trigger*> allTriggers = getAllTriggers();
    if (allTriggers.size() > 0) return allTriggers[0];
    return nullptr;
}

Trigger* Rail::getP3Trigger()
{
    QList<Trigger*> allTriggers = getAllTriggers();
    if (allTriggers.size() > 1) return allTriggers[1];
    return nullptr;
}

int Rail::getRailLength()
{
    return dynamic_cast<QGraphicsPathItem*>(graphicItem)->path().length();
}

int Rail::getConnection(Rail *rail)
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
    if (conectionA0 != nullptr) conectionA0->unconnectRails(dynamic_cast<Rail*>(this));
    if (conectionB0 != nullptr) conectionB0->unconnectRails(dynamic_cast<Rail*>(this));
    if (conectionC1 != nullptr) conectionC1->unconnectRails(dynamic_cast<Rail*>(this));
    if (conectionD1 != nullptr) conectionD1->unconnectRails(dynamic_cast<Rail*>(this));
    deleteArea(0);
    deleteArea(1);
}

