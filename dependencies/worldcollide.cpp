#include "worldcollide.h"

WorldCollide::WorldCollide()
{
    staticChannel ={}; //channel0
    trainChannel ={}; //channel1
    railConnectionChannel ={}; //channel2
}

void WorldCollide::addActorToCollideLists(Actor *actor, int channel)
{
    switch(channel)
    {
        case 0: //staticChannel
        {
            if (staticChannel.indexOf(actor) == -1)
            {
                staticChannel.push_back(actor);
            }
            break;
        }
        case 1: //trainChannel
        {
            if (trainChannel.indexOf(actor) == -1)
            {
            trainChannel.push_back(actor);
            break;
            }
        }
        case 2: //railChannel
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
    QVector<int> channels = removedActor->getCollideChannels(); //all channels what actor use
    for (auto channel : channels)
    {
        switch(channel)
        {
            case 0: //staticChannel
            {
                int removedIndex = staticChannel.indexOf(removedActor);
                if (removedIndex != -1) staticChannel.remove(removedIndex);
                break;
            }
            case 1: //trainChannel
            {
                int removedIndex = trainChannel.indexOf(removedActor);
                if (removedIndex != -1) trainChannel.remove(removedIndex);
                break;
            }
            case 2: //railChannel
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
        case 0: //staticChannel
        {
            if (staticChannel.size() > index)
            {
               return staticChannel[index];
            }
            break;
        }
        case 1: //trainChannel
        {
            if (trainChannel.size() > index)
            {
               return trainChannel[index];
            }
            break;
        }
        case 2: //railChannel
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

void WorldCollide::addTriggerToActor(Actor* actor, int indexOfType, QVector<int> channels, QPoint relativeLocation, float relativeRotation)
{
    for (auto channel : channels)
    {
            addActorToCollideLists(actor, channel);
    }
    actor->addTriggerComponent(indexOfType, channels, relativeLocation, relativeRotation);
}



