#include "trigger.h"

Trigger::Trigger(Component *parent)
{
    blockedChannels = {};
}

void Trigger::setBlockChannels(QVector<int> newBlockChannels)
{
    blockedChannels = newBlockChannels;
}

QVector<int> Trigger::getBlockChannels()
{
    return blockedChannels;
}

Trigger::~Trigger()
{

}
