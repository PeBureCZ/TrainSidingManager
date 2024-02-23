#include "trainselector.h"


TrainSelector::TrainSelector(QObject* parent, QGraphicsItem* newGraphicItem, Actor *actorToConstructing)
    : SelectConstructor(parent, newGraphicItem, actorToConstructing)
{

}

Signal *TrainSelector::getSelectedSignal() const
{
    return selectedSignal;
}

void TrainSelector::setSelectedSignal(Signal *newSelectedSignal)
{
    selectedSignal = newSelectedSignal;
}

Train *TrainSelector::getSelectedTrain() const
{
    return selectedTrain;
}

void TrainSelector::setSelectedTrain(Train *newSelectedTrain)
{
    selectedTrain = newSelectedTrain;
}

void TrainSelector::actualizeConstructor(QPoint newPoint)
{
    setLocation(newPoint,false);
}

