#include "trainselector.h"


TrainSelector::TrainSelector(QObject* parent, QGraphicsItem* newGraphicItem, Actor *actorToConstructing)
    : SelectConstructor(parent, newGraphicItem, actorToConstructing)
{
    selectedTrain = nullptr;
    selectedSignal = nullptr;
}

Signal* TrainSelector::getSelectedSignal()
{
    return selectedSignal;
}

void TrainSelector::setSelectedSignal(Signal *newSelectedSignal)
{
    selectedSignal = newSelectedSignal;
}

Train* TrainSelector::getSelectedTrain()
{
    return selectedTrain;
}

void TrainSelector::setSelectedTrain(Train *newSelectedTrain)
{
    selectedTrain = newSelectedTrain;
}

void TrainSelector::testFce()
{

}

void TrainSelector::actualizeConstructor(QPoint newPoint)
{
    setLocation(newPoint,false);
}

