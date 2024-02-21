#ifndef ACTORCONSTRUCTOR_H
#define ACTORCONSTRUCTOR_H

#include "Actors/actor.h"

class LIB_EXPORT ActorConstructor : public Actor
{
Q_OBJECT
protected:
    Actor* actorConstructing;
public:
    ActorConstructor(QObject* parent = nullptr, QGraphicsItem *newGraphicItem = nullptr, Actor* actorToConstructing = nullptr);
    virtual void actualizeConstructor(QPoint newPoint);
    Actor *getActorConstructing();
    Actor *setActorConstructing(Actor *newActor);
signals:

public slots:
};

#endif // ACTORCONSTRUCTOR_H
