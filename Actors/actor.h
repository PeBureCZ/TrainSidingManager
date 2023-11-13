#ifndef ACTOR_H
#define ACTOR_H

#include <QString>
#include <QPoint>
#include <QGraphicsPathItem>
#include "Components/spherecollider.h"
#include "worldcollide.h"

class Actor
{
protected:
    QString name;
    QPoint location;
    QGraphicsItem* graphicItem;
    float rotation;
    QVector<Trigger*> triggers;
    bool collisionEnabled;
    WorldCollide* worldCollideObject;
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
    void addTriggerComponent(QPoint relativeLocation, float relativeRotation, int indexOfType, QVector<int> channels);
    void enableCollision(WorldCollide* collisionObject);

    virtual ~Actor();
};

#endif // ACTOR_H
