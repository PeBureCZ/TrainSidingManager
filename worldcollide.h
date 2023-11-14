#ifndef WORLDCOLLIDE_H
#define WORLDCOLLIDE_H

#include <QDebug>

#include <QVector>
#include <QPoint>
#include <QLineF>
#include "Actors/actor.h"

class WorldCollide
{
protected:
    QVector<Actor*> railChannel;
    QVector<Actor*> staticChannel;
    QVector<Actor*> trainChannel;
    void addActorToCollideLists(Actor* actor, int channel);
public:
    WorldCollide();
    QString test();
    void removeActorFromCollideLists(Actor* removedActor);
    Actor* getActorFromTriggerList(int inChannel, int index);
    int getSizeOfRailChannel();
    int getSizeOfStaticChannel();
    int getSizeOfTrainChannel();
    void addTriggerToActor(Actor *actor, int indexOfType, QVector<int> channels, QPoint relativeLocation, float relativeRotation);
};

#endif // WORLDCOLLIDE_H
