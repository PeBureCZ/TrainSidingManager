#ifndef ACTOR_H
#define ACTOR_H

#include <QString>
#include <QPoint>
#include <QGraphicsPathItem>
#include "Components/collider.h"

class Actor
{
protected:
    QString name;
    QPoint location;
    QGraphicsItem* graphicItem;
    float rotation;
private:
public:
    Actor(QGraphicsItem *newGraphicItem);
    QGraphicsItem* getGraphicItem();
    virtual void setName(QString newName); //virtual need for polymorph
    QString getName();
    void setRotation(float newRotation);
    float getRotation();
    void setLocation(QPoint newLocation);
    QPoint getLocation();
    virtual ~Actor();
};

#endif // ACTOR_H
