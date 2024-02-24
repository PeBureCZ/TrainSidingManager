#ifndef ACTOR_H
#define ACTOR_H

#include <QDebug>

#include <QString>
#include <QPoint>
#include <QGraphicsPathItem>
#include "../Components/spherecollider.h"
#include "../Components/boxcollider.h"
#include <QObject>
#include "lib_global.h"

//ENUMS
#include "dependencies/Enums/ComponentsEnum.h"

class LIB_EXPORT Actor : public QObject
{
Q_OBJECT
protected:
    QString name;
    QPoint location;
    QPoint graphicLocation;
    QGraphicsItem* graphicItem;
    QVector<Trigger*> triggers;
    QVector<int> calledCollisions;
    QList<Actor*> actorsInCollision;
    float rotation;
    float graphicRotation;
    bool collisionRecieveEnabled;
    bool collisionCallEnabled;

private:
public:
    Actor(QObject *parent = nullptr, QGraphicsItem *newGraphicItem = nullptr);
    QGraphicsItem* getGraphicItem();
    QPoint getGraphicLocation();
    QVector<int> recieveCollideChannels();
    QVector<int> callCollideChannels();
    QString getName();
    QPoint getLocation();
    QPoint getRotatedPointArountPivot(const QPoint point, const QPoint pivot, const double angle);
    QVector<Trigger*> getAllTriggers();

    void setGraphicRotation(const float newRotation);
    void setRotation(const float newRotation, bool setGraphic);
    void setCallCollisionChannels(const QVector<int> newCollisions);
    void setGraphicLocation(QPoint newLocation);
    void setLocation(QPoint newLocation, bool setGraphic); //overloaded function
    void setLocation(QPointF newLocation, bool setGraphic); //overloaded function
    void createTriggerInActor(int indexOfType, QVector<int> channels, QPoint relativeLocation, float relativeRotation, int radius);

    float getRotation();
    int getDistance(QPoint pointA, QPoint pointB);

    bool canRecieveCollision();
    bool canCallCollision();

    virtual void setName(QString newName); //virtual need for polymorph
    virtual void actualizeGraphicLocation();
    virtual void actualizeGraphicRotation();
    virtual void calledCollisionEvent(const QList<Actor*> isInCollision); //overrided
    virtual void setRailObjectBoxCollider(); //overrided
    virtual void tickEvent();
    virtual void actorLeaveFromCollision(Actor* actor);
    virtual void actorEnterInCollision(Actor* actor);
    virtual ~Actor();
signals:

public slots:
};

#endif // ACTOR_H
