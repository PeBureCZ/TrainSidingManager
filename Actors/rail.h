#ifndef RAIL_H
#define RAIL_H

#include "railwayobject.h"
#include <QGraphicsPathItem>

class Rail : public RailwayObject
{
Q_OBJECT
protected:
    QPoint P0; //start point - ABSOLUTE
    QPoint P1; //first curve control point - RELATIVE TO P0
    QPoint P2; //second curve control point - RELATIVE TO P0
    QPoint P3; //end point - RELATIVE TO P0
    Rail* conectionA0;
    Rail* conectionB0;
    Rail* conectionC1;
    Rail* conectionD1;
    bool lined;
public:
    Rail(QObject *parent = nullptr, QGraphicsItem* newGraphicItem = nullptr);
    QPointF getP0WorldLocation();
    QPointF getP1RelativeLocation();
    QPointF getP2RelativeLocation();
    QPointF getP3RelativeLocation();
    Rail* getConnectedRail(int connection);

    bool getLined();
    int getRailLength();
    int getConnection(Rail* rail);

    void setConnectedRail(Rail *connectedRail, int connection);
    void setP0WorldLocation(QPoint newPoint);
    void setP1RelativeLocation(QPoint newPoint);
    void setP2RelativeLocation(QPoint newPoint);
    void setP3RelativeLocation(QPoint newPoint);
    void setLined(bool newBool);
    void connectRails(Rail* connectedRail, bool connectedAtStart);
    void unconnectRails(Rail* unconnectedRail);
    void smoothP3PointByC1();
    ~Rail();
signals:

public slots:
};

#endif // RAIL_H
