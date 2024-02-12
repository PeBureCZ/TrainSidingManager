#ifndef RAILOBJECTCONSTRUCTOR_H
#define RAILOBJECTCONSTRUCTOR_H

#include "actorconstructor.h"
#include <QObject>

class LIB_EXPORT RailobjectConstructor : public ActorConstructor
{
    Q_OBJECT
public:
    explicit RailobjectConstructor(QObject *parent = nullptr, QGraphicsItem *newGraphicItem = nullptr, Actor *actorToConstructing = nullptr);
};

#endif // RAILOBJECTCONSTRUCTOR_H
