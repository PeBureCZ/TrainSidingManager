#ifndef ACTOR_H
#define ACTOR_H

#include <QDebug>

#include <QString>
#include <QPoint>
#include <QGraphicsPathItem>
#include "Components/spherecollider.h"
#include "Components/boxcollider.h"

#include <QObject>

class Actor : public QObject
{
Q_OBJECT
protected:
    QString name;
    QPoint location;
    QPoint graphicLocation;
    QGraphicsItem* graphicItem;
    QVector<Trigger*> triggers;
    QVector<int> calledCollisions;
    float rotation;
    bool collisionRecieveEnabled;
    bool collisionCallEnabled;
    void setGraphicLocation(QPoint newLocation);
private:
public:
    Actor(QObject *parent = nullptr, QGraphicsItem *newGraphicItem = nullptr);
    QGraphicsItem* getGraphicItem();
    QVector<int> recieveCollideChannels();
    QVector<int> callCollideChannels();
    QString getName();
    QPoint getLocation();
    QVector<Trigger*> getAllTriggers();

    void setRotation(const float newRotation);
    void setCallCollisionChannels(const QVector<int> newCollisions);
    void setLocation(QPoint newLocation, bool setGraphic);
    void addTriggerComponent(int indexOfType, QVector<int> channels, QPoint relativeLocation, float relativeRotation, int radius);

    float getRotation();
    int getDistance(QPoint pointA, QPoint pointB);

    bool canRecieveCollision();
    bool canCallCollision();

    //public virtual
    virtual void setName(QString newName); //virtual need for polymorph
    virtual void actualizeGraphicLocation();
    virtual void actorCollide(const QList<Actor*> actorsInCollision); //overrided
    virtual void setObjectBoxCollider(); //overrided
    virtual void tickEvent();
    virtual ~Actor();
signals:

public slots:
};

#endif // ACTOR_H
