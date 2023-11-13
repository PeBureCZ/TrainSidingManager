#ifndef WORLDCOLLIDE_H
#define WORLDCOLLIDE_H

#include <QVector>
#include <QPoint>
#include <QLineF>
#include "Components/spherecollider.h"

class WorldCollide
{
protected:
    QVector<Trigger*> railChannel;
    QVector<Trigger*> staticChannel;
    QVector<Trigger*> trainChannel;
public:
    WorldCollide();
    QString test();
    void addTriggerToList(Trigger* newTrigger, int channel);
    void removeTriggerFromList(Trigger* removedTrigger, int channel);
    Trigger* getTrigger(int inChannel, int index);
    int getSizeOfRailChannel();
    int getSizeOfStaticChannel();
    int getSizeOfTrainChannel();
};

#endif // WORLDCOLLIDE_H
