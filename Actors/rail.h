#ifndef RAIL_H
#define RAIL_H

#define VISUAL_AREA_SIZE 40

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
    QGraphicsItem *startArea;
    QGraphicsItem* endArea;
public:
    Rail(QObject *parent = nullptr, QGraphicsItem* newGraphicItem = nullptr);
    QPointF getP0WorldLocation();
    QPointF getP1RelativeLocation();
    QPointF getP2RelativeLocation();
    QPointF getP3RelativeLocation();
    Rail* getConnectedRail(const int connection);

    bool getLined();
    int getRailLength();
    int getConnection(Rail* rail);
    int getVisualAreaSize();

    void setConnectedRail(Rail *connectedRail, const int connection);
    void setP0WorldLocation(const QPoint newPoint);
    void setP1RelativeLocation(const QPoint newPoint);
    void setP2RelativeLocation(const QPoint newPoint);
    void setP3RelativeLocation(const QPoint newPoint);
    void setLined(const bool newBool);
    void createArea(const int area, QGraphicsItem *graphicItem);
    void deleteArea(const int area);
    void setVisibilityOfArea(const int area, const bool visible);
    void actualizeAreasPosition();
    void connectRails(Rail* connectedRail, const bool connectedAtStart);
    void unconnectRails(Rail* unconnectedRail);
    void smoothP3PointByC1();
    ~Rail();
signals:

public slots:
};

#endif // RAIL_H
