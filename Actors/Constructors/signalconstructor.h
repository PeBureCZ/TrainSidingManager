#ifndef SIGNALCONSTRUCTOR_H
#define SIGNALCONSTRUCTOR_H

#include <Actors/Constructors/railobjectconstructor.h>
#include <QObject>

class SignalConstructor : public RailobjectConstructor
{
    Q_OBJECT
public:
    explicit SignalConstructor(QObject *parent = nullptr, QGraphicsItem *newGraphicItem = nullptr, Actor *actorToConstructing = nullptr);
};

#endif // SIGNALCONSTRUCTOR_H
