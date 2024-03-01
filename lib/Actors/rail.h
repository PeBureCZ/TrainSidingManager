#ifndef RAIL_H
#define RAIL_H

#include "railwayobject.h"
#include <QGraphicsItem>
#include "Components/trigger.h"
#include "Actors/signal.h"
#include "dependencies/settings.h"
#include <QColor>

#include <QPen>

class LIB_EXPORT Rail : public RailwayObject
{
Q_OBJECT
protected:
    const int VISUAL_AREA_SIZE = 40;
    QPoint P0; //start point - ABSOLUTE
    QPoint P1; //first curve control point - RELATIVE TO P0
    QPoint P2; //second curve control point - RELATIVE TO P0
    QPoint P3; //end point - RELATIVE TO P0
    Rail* conectionA0;
    Rail* conectionB0;
    Rail* conectionC1;
    Rail* conectionD1;
    Signal* signalP0;
    Signal* signalP3;
    bool lined;
    QGraphicsItem *startArea;
    QGraphicsItem* endArea;
    bool occupied;
    bool visuallyOccupied;

public:
    Rail(QObject *parent = nullptr, QGraphicsItem* newGraphicItem = nullptr);
    QPointF getP0WorldLocation();
    QPointF getP1RelativeLocation();
    QPointF getP2RelativeLocation();
    QPointF getP3RelativeLocation();
    Rail* getConnectedRail(const int connection);
    QGraphicsItem *getAreaGraphic(const int area);
    Trigger* getP0Trigger();
    Trigger *getP3Trigger();
    Signal* getSignal(int numberOfEndPoint) const;

    bool getLined();
    bool getOccupied();

    int getLengthOfRail() const;
    int getConnection(const Rail *rail) const;
    int getVisualAreaSize();

    void setConnectedRail(Rail *connectedRail, const int connection);
    void setP0WorldLocation(const QPoint newPoint);
    void setP1RelativeLocation(const QPoint newPoint);
    void setP2RelativeLocation(const QPoint newPoint);
    void setP3RelativeLocation(const QPoint newPoint);
    void setLined(const bool newBool);
    void createArea(const int area, QGraphicsItem *graphicItem);
    void deleteArea(const int area);
    void setVisibilityOfArea(const int area, const bool visible, QColor color);
    void actualizeAreasPosition();
    void connectRails(Rail* connectedRail, const bool connectedAtStart);
    void unconnectRail(Rail* unconnectedRail);
    void smoothConnectionA0(bool changeP1Distance);
    void smoothConnectionC1(bool changeP2Distance);
    void setOccupied(const bool isOccupied, bool setGraphic);
    void setRailColor(QColor color, int layerEnum);
    void moveRailPoints(QPoint newP0, QPoint newP1, QPoint newP2, QPoint newP3);
    void setRailObjectBoxCollider() override;
    void addSignal(int numberOfEndPoint, Signal *signalActor);

    void actorLeaveFromCollision(Actor* actor) override; //used if signal is deleted

    ~Rail();

signals:

public slots:
};

#endif // RAIL_H
