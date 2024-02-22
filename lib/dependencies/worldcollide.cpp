#include "worldcollide.h"

WorldCollide::WorldCollide(QObject *parent)
{
    staticChannel ={}; //channel0
    trainChannel ={}; //channel1
    railConnectionChannel ={}; //channel2
}

void WorldCollide::addActorToCollideLists(Actor *actor, int channel)
{
    switch(channel)
    {
        case STATIC_CHANNEL:
        {
            if (staticChannel.indexOf(actor) == -1)
            {
                staticChannel.push_back(actor);
            }
            break;
        }
        case TRAIN_CHANNEL:
        {
            if (trainChannel.indexOf(actor) == -1)
            {
            trainChannel.push_back(actor);
            break;
            }
        }
        case RAIL_CHANNEL:
        {
            if (railConnectionChannel.indexOf(actor) == -1)
            {
            railConnectionChannel.push_back(actor);
            break;
            }
        }
    }
}

void WorldCollide::removeActorFromCollideLists(Actor *removedActor)
{
    QVector<int> channels = removedActor->recieveCollideChannels(); //all channels what actor use
    for (auto channel : channels)
    {
        switch(channel)
        {
            case STATIC_CHANNEL:
            {
                int removedIndex = staticChannel.indexOf(removedActor);
                if (removedIndex != -1) staticChannel.remove(removedIndex);
                break;
            }
            case TRAIN_CHANNEL:
            {
                qDebug() << "remove from collide list, size: " << trainChannel.size();
                int removedIndex = trainChannel.indexOf(removedActor);
                if (removedIndex != -1) trainChannel.remove(removedIndex);
                qDebug() << "remove from collide list, size after: " << trainChannel.size();
                break;
            }
            case RAIL_CHANNEL:
            {
                int removedIndex = railConnectionChannel.indexOf(removedActor);
                if (removedIndex != -1) railConnectionChannel.remove(removedIndex);
                break;
            }
        }
    }
}

Actor *WorldCollide::getActorFromTriggerList(int inChannel, int index)
{
    switch (inChannel)
    {
        case STATIC_CHANNEL:
        {
            if (staticChannel.size() > index)
            {
               return staticChannel[index];
            }
            break;
        }
        case TRAIN_CHANNEL:
        {
            if (trainChannel.size() > index)
            {
               return trainChannel[index];
            }
            break;
        }
        case RAIL_CHANNEL:
        {
            if (railConnectionChannel.size() > index)
            {
                return railConnectionChannel[index];
            }
            break;
        }
    }
    return nullptr;
}

int WorldCollide::getSizeOfRailChannel()
{
    return railConnectionChannel.size();
}

int WorldCollide::getSizeOfStaticChannel()
{
    return staticChannel.size();
}

int WorldCollide::getSizeOfTrainChannel()
{
    return trainChannel.size();
}

void WorldCollide::addCollideTriger(Actor* actor, int indexOfType, QVector<int> channels, QPoint relativeLocation, float relativeRotation, int radius)
{
    //for check collisions - e.g. find actors in collide list (saved in worlmap) under cursor
    for (auto channel : channels)
    {
            addActorToCollideLists(actor, channel);
    }
    actor->createTriggerInActor(indexOfType, channels, relativeLocation, relativeRotation, radius);
}



