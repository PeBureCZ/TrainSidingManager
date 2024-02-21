#ifndef PORTAL_H
#define PORTAL_H

#include "actor.h"
#include <QObject>
#include "Actors/rail.h"

class LIB_EXPORT Portal : public Actor
{
    Q_OBJECT
protected:
    Rail* connectedRail;
    int connectedToArea;
public:
    explicit Portal(QObject *parent = nullptr, QGraphicsItem *newGraphicItem = nullptr);
    void setConnectedRail(Rail* newConnectedRail);
    Rail* getConnectedRail();
    int getConectedArea();

    //~Portal();
};

#endif // PORTAL_H
