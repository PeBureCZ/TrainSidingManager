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
    QGraphicsItem* graphicItem;
    float rotation;
    QVector<Trigger*> triggers;
    bool collisionEnabled;
private:
public:
    Actor(QObject *parent = nullptr, QGraphicsItem *newGraphicItem = nullptr);
    QGraphicsItem* getGraphicItem();
    QVector<int> getCollideChannels();
    QString getName();
    QPoint getLocation();
    QVector<Trigger*> getAllTriggers();

    void setRotation(float newRotation);
    float getRotation();
    void setLocation(QPoint newLocation);
    void addTriggerComponent(int indexOfType, QVector<int> channels, QPoint relativeLocation, float relativeRotation);
    virtual void setName(QString newName); //virtual need for polymorph
    bool canCollide();
    virtual void setObjectBoxCollider(); //overrided
    virtual void tickEvent();
    virtual ~Actor();
signals:

public slots:
};

#endif // ACTOR_H
