#include "railnavigation.h"


void RailNavigation::makePath(Train* train, Signal *nearestSignal)
{
    if (train != nullptr && nearestSignal != nullptr)
    {
        Rail* lastRail;

        if (train->getRemainingPath().size() > 0) lastRail = train->getRemainingPath().last();
        else lastRail = train->getActualRail();

        bool direction = TrainNavigation::checkDirectionOnLatestRail(train->getRemainingPath(), train->getActualRail(), train->getDirectionToRailEnd());
        Rail* railToFind = dynamic_cast<Rail*>(nearestSignal->getRailActor());
        QList<Rail*> needTestRails = {lastRail};
        QList<bool> testedRailDirection = {direction};

        QList<Rail*> findedRails = {};
        //QList<Rail*> findedDirections = {};

        int repeat = 300; //number of rails to check in order to find the path
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
                //scan connected rail of testedRail
                if (testedRail->getConnectedRail(i) != nullptr) //true = on connection is rail
                {
                    Rail* newRailFinded = testedRail->getConnectedRail(i);
                    if (newRailFinded->getOccupied()) continue;

                    int conectionToPreviousRail = newRailFinded->getConnection(testedRail);
                    if (conectionToPreviousRail <=1) conectionToPreviousRail = 0;
                    else conectionToPreviousRail  = 1;

                    bool newDirection;
                    (conectionToPreviousRail == 0) ? newDirection = true : newDirection = false;

                    if (newRailFinded == railToFind)
                    {
                        //check if the track is in opposite direction
                        int railEndOfSignal;
                        (newRailFinded->getSignal(0) == nearestSignal) ? railEndOfSignal = 0 : railEndOfSignal = 1;
                        if (railEndOfSignal != newDirection)
                        {
                            //It is necessary to remove the wrong rail because it may be prioritized over the rail with the correct direction during reverse pathfinding
                            int indexOfWrongRail = findedRails.indexOf(testedRail);
                            if (indexOfWrongRail != -1) findedRails.removeAt(indexOfWrongRail);
                            continue;
                        }
                    }

                    int connectionToRailToFind = newRailFinded->getConnection(railToFind);
                    if (connectionToRailToFind != -1)
                    {
                        //newRailFinded is connected to railToFind! but is direction right?
                        if (connectionToRailToFind <=1) connectionToRailToFind = 0;
                        else connectionToRailToFind = 1;

                        if (conectionToPreviousRail == connectionToRailToFind) continue; //finded rail is in wrong direction
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

        if (finded)
        {
            //REVERSED PATHFINDING
            while(true) // remove other found rails at the end of the list if they are not the Rails looking for
            {
                Rail* lastRailInList = findedRails.last();
                if (railToFind == lastRailInList) break;
                else findedRails.removeLast();
            }
            for (int i = findedRails.size() - 1; i > 0; i--)
            {
                Rail* railFromList = findedRails[i];

                if (railFromList->getConnection(findedRails[i-1]) != -1); //part of path finded! Skip code...
                else if (railFromList != railToFind )
                {
                    //not first and not last rails
                    int connectionToPrevious = railFromList->getConnection(findedRails[i-1]);
                    int connectionToNext = railFromList->getConnection(findedRails[i+1]);

                    //transfer to railEnds number
                    if (connectionToPrevious != -1 && connectionToPrevious <= 1) connectionToPrevious = 0;
                    if (connectionToNext != -1 && connectionToNext <= 1) connectionToPrevious = 0;
                    if (connectionToPrevious != -1 && connectionToPrevious >= 2) connectionToPrevious = 1;
                    if (connectionToNext != -1 && connectionToNext >= 2) connectionToPrevious = 1;

                    if (connectionToNext != -1 && connectionToPrevious == connectionToNext) findedRails.removeAt(i-1);
                    else findedRails.removeAt(i-1);
                }
                else findedRails.removeAt(i-1);
            }

            //check first rail in list
            if (findedRails.size() > 1 && dynamic_cast<Rail*>(findedRails[0])->getConnection(dynamic_cast<Rail*>(findedRails[1])) == -1)
            {
                findedRails.removeAt(0);
            }

            //Check if the Rail is used in path multiple times
            QList<Rail*> outputPath = {};
            for (auto rail : findedRails)
            {
                if (outputPath.indexOf(rail) == -1) outputPath.push_back(rail);
                else
                {
                   qDebug() << "Rail is used in path multiple times";
                   return;
                }
            }  
            train->addNextPartOfPath(outputPath);
            train->recalculateRemainToPathEnd();
            TrainNavigation::checkSignalsOnPath(train->getActualRail(), train->getRemainingPath(),train->getDirectionToRailEnd(),train->getRemainToPathEnd()- train->getActualSpeed());
            if (train->getAutopilot()) train->setTravelDistance(train->getRemainToPathEnd());
        }
        else qDebug() << "the path was not found!";
    }
}
