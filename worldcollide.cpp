#include "worldcollide.h"

WorldCollide::WorldCollide()
{
    staticChannel ={}; //channel0
    trainChannel ={}; //channel1
    railChannel ={}; //channel2
}

QString WorldCollide::test()
{
    return QString::number(railChannel.size());
}


void WorldCollide::addActorToCollideLists(Actor *actor, int channel)
{
    switch(channel)
    {
        case 0: //staticChannel
        {
            staticChannel.push_back(actor);
            break;
        }
        case 1: //trainChannel
        {
            trainChannel.push_back(actor);
            break;
        }
        case 2: //railChannel
        {
            railChannel.push_back(actor);
            break;
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
                int removedIndex = railChannel.indexOf(removedActor);
                if (removedIndex != -1) railChannel.remove(removedIndex);
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
            if (railChannel.size() > index)
            {
                return railChannel[index];
            }
            break;
        }
    }
    return nullptr;
}

int WorldCollide::getSizeOfRailChannel()
{
    return railChannel.size();
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
    if (actor->canCollide()) //add to list if isn´t in list yet
    {
        for (auto channel : channels)
        {
            switch (indexOfType)
            {
            case 0: //SphereCollider
            {
                addActorToCollideLists(actor, channel);
                break;
            }
            case 1:
            {
                break;
            }
            case 2:
            {
                break;
            }
            defaul: {}
            }
        }
    }
    actor->addTriggerComponent(indexOfType, channels, relativeLocation, relativeRotation);
}

