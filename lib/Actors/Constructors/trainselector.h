#ifndef TRAINSELECTOR_H
#define TRAINSELECTOR_H

#include "selectconstructor.h"
#include <QObject>
#include "Actors/train.h"
#include "Actors/rail.h"
#include "Actors/signal.h"

class TrainSelector : public SelectConstructor
{
    Q_OBJECT
protected:
    Signal* selectedSignal = nullptr;
    Train* selectedTrain = nullptr;
public:
    explicit TrainSelector(QObject* parent = nullptr, QGraphicsItem* newGraphicItem = nullptr, Actor *actorToConstructing = nullptr);
    void actualizeConstructor(QPoint newPoint) override;

    Signal *getSelectedSignal() const;
    void setSelectedSignal(Signal *newSelectedSignal);
    Train *getSelectedTrain() const;
    void setSelectedTrain(Train *newSelectedTrain);
};

#endif // TRAINSELECTOR_H
