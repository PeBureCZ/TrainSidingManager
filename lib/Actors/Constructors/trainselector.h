#ifndef TRAINSELECTOR_H
#define TRAINSELECTOR_H

#include "selectconstructor.h"
#include <QObject>
#include "Actors/train.h"
#include "Actors/rail.h"

class LIB_EXPORT TrainSelector : public SelectConstructor
{
    Q_OBJECT
protected:
    Signal* selectedSignal = nullptr;
    Train* selectedTrain = nullptr;
public:
    explicit TrainSelector(QObject* parent = nullptr, QGraphicsItem* newGraphicItem = nullptr, Actor *actorToConstructing = nullptr);
    void actualizeConstructor(QPoint newPoint, int zoomLevel) override;

    Signal *getSelectedSignal();
    void setSelectedSignal(Signal *newSelectedSignal);
    Train *getSelectedTrain();
    void setSelectedTrain(Train *newSelectedTrain);
    void findPathToSignal();
};

#endif // TRAINSELECTOR_H
