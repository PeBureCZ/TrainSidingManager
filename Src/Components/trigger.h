#ifndef TRIGGER_H
#define TRIGGER_H

#include "component.h"
#include <QVector>


class Trigger : public Component
{
 Q_OBJECT
protected:
    QVector<int> blockedChannels;
public:
    Trigger(Component *parent = nullptr);
    void setBlockChannels(QVector<int> newBlockChannels);
    QVector<int> getBlockChannels();
    virtual ~Trigger();
};

#endif // TRIGGER_H
