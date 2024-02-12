#ifndef WORLDCOLLIDE_H
#define WORLDCOLLIDE_H

#include <QDebug>

#include <QVector>
#include <QPoint>
#include <QLineF>
#include "Actors/actor.h"

//ENUMS
#include "Enums/BlockChannels.h"

class LIB_EXPORT WorldCollide : public QObject
{
Q_OBJECT
protected:
    QVector<Actor*> railConnectionChannel; //0
    QVector<Actor*> staticChannel; //1
    QVector<Actor*> trainChannel; //2
    void addActorToCollideLists(Actor* actor, int channel);
public:
    WorldCollide(QObject *parent = nullptr);
    void removeActorFromCollideLists(Actor* removedActor);
    Actor* getActorFromTriggerList(int inChannel, int index);
    int getSizeOfRailChannel();
    int getSizeOfStaticChannel();
    int getSizeOfTrainChannel();
    void addTriggerToActor(Actor *actor, int indexOfType, QVector<int> channels, QPoint relativeLocation, float relativeRotation, int radius);
};

#endif // WORLDCOLLIDE_H
