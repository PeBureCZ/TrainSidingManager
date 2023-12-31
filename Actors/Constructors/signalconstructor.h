#ifndef SIGNALCONSTRUCTOR_H
#define SIGNALCONSTRUCTOR_H

#include <Actors/Constructors/railobjectconstructor.h>
#include <QObject>
#include <QGraphicsView>

class SignalConstructor : public RailobjectConstructor
{
    Q_OBJECT
public:
    explicit SignalConstructor(QObject *parent = nullptr, QGraphicsItem *newGraphicItem = nullptr, Actor *actorToConstructing = nullptr);
    void actualizeConstructor(QPoint newPoint) override;
    ~SignalConstructor();
};

#endif // SIGNALCONSTRUCTOR_H
