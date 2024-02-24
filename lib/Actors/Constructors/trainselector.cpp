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

void TrainSelector::findPathToSignal()
{
    if (selectedTrain != nullptr && selectedSignal != nullptr)
    {
        Rail* lastRail;
        if (selectedTrain->getTrainPath().size() > 0)
        {
            lastRail = selectedTrain->getTrainPath().last();
        }
        else
        {
            lastRail = selectedTrain->getActualRail();
        }
        bool direction = TrainNavigation::checkDirectionOnLatestRail(selectedTrain->getTrainPath(), selectedTrain->getActualRail(), selectedTrain->getDirectionToRailEnd());

        Rail* railToFind = dynamic_cast<Rail*>(selectedSignal->getRailActor());

        QList<Rail*> needTestRails = {lastRail};
        QList<bool> testedRailDirection = {direction};

        QList<Rail*> findedRails = {};
        //QList<Rail*> findedDirections = {};

        int repeat = 300;
        bool finded = false;
        while (repeat > 0 && needTestRails.size() > 0)
        {
            Rail* testedRail = needTestRails[0];
            if (testedRail == railToFind)
            {
                finded = true;
                break; // rail is finded!
            }
            direction = testedRailDirection[0];

            //if direction is true -> try to find rail on connection C1 or D1 (2,3), else on A0, B0 (0,1)
            int testedRailConnection = 0;
            if (direction) testedRailConnection += 2;

            int firstIndex = testedRailConnection;
            int lastIndex = testedRailConnection + 2;

            for (int i = firstIndex; i < lastIndex; i++)
            {
                if (testedRail->getConnectedRail(i) != nullptr) //true = on connection is rail
                {
                    Rail* newRailFinded = testedRail->getConnectedRail(i);
                    if (newRailFinded->getOccupied()) continue;
                    int conectionToPreviousRail = newRailFinded->getConnection(testedRail);
                    bool newDirection;
                    (conectionToPreviousRail <= 1) ? newDirection = true : newDirection = false;

                    if (newRailFinded == railToFind)
                    {
                        //check if the track is in opposite direction
                        int railEndOfSignal;
                        (newRailFinded->getSignal(0) == selectedSignal) ? railEndOfSignal = 0 : railEndOfSignal = 1;
                        qDebug() << "signal is on end: " << railEndOfSignal;
                        qDebug() << "new direction: " << newDirection;
                        if (railEndOfSignal != newDirection)
                        {
                            qDebug() << "reversed direction!";
                            continue;
                        }
                    }
                    testedRailDirection.push_back(newDirection);

                    findedRails.push_back(newRailFinded); //add to temporal list
                    needTestRails.push_back(newRailFinded);
                }
            }
            repeat--;
            needTestRails.removeAt(0);
            testedRailDirection.removeAt(0);
        }
        qDebug() << "repeat remaining: " << repeat;

        if (finded)
        {
            while(true)
            {
                Rail* lastRailInList = findedRails.last();
                if (railToFind == lastRailInList)
                {
                    break;
                }
                else
                {
                    findedRails.removeLast();
                }
            }
            qDebug() << "findedRails size before reduction is " << findedRails.size();
            for (int i = findedRails.size() - 1; i > -1; i--)
            {
                //qDebug() << "try rail " << i;
                Rail* railFromList = findedRails[i];
                if (i > 0 && railFromList->getConnection(findedRails[i-1]) != -1)
                {
                    //qDebug() << "find reverse!";
                }
                else if (i > 0)
                {
                    //qDebug() << "discard " << i-1;
                    findedRails.removeAt(i-1);
                }
                //else qDebug() << "end";
            }
            qDebug() << "findedRails size after reduction is " << findedRails.size();
            selectedTrain->addNextPartOfPath(findedRails);

            selectedTrain->setActualSpeed(selectedTrain->getActualSpeed()+1);
        }
        else qDebug() << "the path was not found!";
    }
}

void TrainSelector::actualizeConstructor(QPoint newPoint)
{
    setLocation(newPoint,false);
}

