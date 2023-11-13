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


void WorldCollide::addTriggerToList(Trigger *newTrigger, int channel)
{
    switch(channel)
    {
        case 0: //staticChannel
        {
            staticChannel.push_back(newTrigger);
            break;
        }
        case 1: //trainChannel
        {
            trainChannel.push_back(newTrigger);
            break;
        }
        case 2: //railChannel
        {
            railChannel.push_back(newTrigger);
            break;
        }
    }
}

void WorldCollide::removeTriggerFromList(Trigger *removedTrigger, int channel)
{
    switch(channel)
    {
        case 0: //staticChannel
        {
           int removedIndex = staticChannel.indexOf(removedTrigger);
           staticChannel.remove(removedIndex);
           break;
        }
        case 1: //trainChannel
        {
           int removedIndex = staticChannel.indexOf(removedTrigger);
           trainChannel.remove(removedIndex);
           break;
        }
        case 2: //railChannel
        {
           int removedIndex = staticChannel.indexOf(removedTrigger);
           railChannel.remove(removedIndex);
           break;
        }
    }
}

Trigger *WorldCollide::getTrigger(int inChannel, int index)
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
    return staticChannel.size();
}

int WorldCollide::getSizeOfStaticChannel()
{
    return trainChannel.size();
}

int WorldCollide::getSizeOfTrainChannel()
{
    return railChannel.size();
}

