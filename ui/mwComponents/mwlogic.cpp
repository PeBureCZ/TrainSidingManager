#include "mwComponents/mwlogic.h"

mwlogic::mwlogic(MainWindow *parent)
    : MainWindow{parent}
{
    menuSelected = EDIT_MODE_START;
    playModeActualized = false;
    elapsedTime = 0;
}

void mwlogic::actualizeMap()
{
    if (menuSelected >= PLAY_MODE_START)
    {
        if (!playModeActualized) //actualize only one time per "updateWorld" function
        {
            world->actualizePlayMode();
            playModeActualized = true;
        }
        if (elapsedTime > 200) //actualize play mode only one time per 1 second
        {
            world->updateWorld();
            elapsedTime -= 200;
            playModeActualized = false;
        }
        else world->actualizeConstructorPerTick();
    }
    else
    {
        world->actualizeEditor();
        world->updateWorld();
        elapsedTime = 0;
    }
    managerConsole->reduceTimeSpan(1);
}

void mwlogic::actualizeDeltaTime(qint64 deltaTime)
{
    if (menuSelected >= PLAY_MODE_START) elapsedTime += deltaTime;
}

void mwlogic::playButSwitch(bool editMode)
{
    MainWindow::playButSwitch(editMode);
    InterfaceSet(menuSelected);
}

void mwlogic::selectMenuSwitch(bool selectMode)
{
    MainWindow::selectMenuSwitch(selectMode);
    InterfaceSet(menuSelected);
}

void mwlogic::addConstructor(int constructorType)
{
    world->deleteConstructor();
    ConsoleTextsStruct console;
    switch (constructorType)
    {
    case RAIL_CONSTRUCTOR:

        world->addActor(RAIL_CONSTRUCTOR);
        managerConsole->printToConsole(console.messageText[RAIL_CONSOLE_TEXT1], DEFAULT_COLOR, LONG_DURATION);
        managerConsole->printToConsole(console.messageText[RAIL_CONSOLE_TEXT2], DEFAULT_COLOR, LONG_DURATION);
        break;
    case SIGNAL_CONSTRUCTOR:
        world->addActor(SIGNAL_CONSTRUCTOR);
        managerConsole->printToConsole(console.messageText[SIGNAL_CONSOLE_TEXT1], DEFAULT_COLOR, LONG_DURATION);
        managerConsole->printToConsole(console.messageText[SIGNAL_CONSOLE_TEXT2], DEFAULT_COLOR, LONG_DURATION);
        break;
    case RAIL_SELECTOR:
        world->addActor(RAIL_SELECTOR);
        managerConsole->printToConsole(console.messageText[RAIL_SELECTOR_CONSOLE_TEXT], DEFAULT_COLOR, LONG_DURATION);
        break;
    case PORTAL_CONSTRUCTOR:
        world->addActor(PORTAL_CONSTRUCTOR);
        managerConsole->printToConsole(console.messageText[PORTAL_CONSOLE_TEXT1], DEFAULT_COLOR, LONG_DURATION);
        managerConsole->printToConsole(console.messageText[PORTAL_CONSOLE_TEXT2], DEFAULT_COLOR, LONG_DURATION);
        break;
    case TRAIN_SELECTOR:
        world->addActor(TRAIN_SELECTOR);
        //managerConsole->printToConsole(console.messageText[PORTAL_CONSOLE_TEXT1], DEFAULT_COLOR, LONG_DURATION);
        //managerConsole->printToConsole(console.messageText[PORTAL_CONSOLE_TEXT2], DEFAULT_COLOR, LONG_DURATION);
        break;
    default: {}
    }
}

void mwlogic::constructRail(QPoint point)
{
    RailConstructor* actualRailConstructor = dynamic_cast<RailConstructor*>(world->getActualConstructor());
    Rail* nearestRail = actualRailConstructor->getNearestRail();
    int createRailByStyle = -1;
    int zoom = world->getWorldView()->getZoomLevel();
    int nearestPoint = -1;

    if (actualRailConstructor != nullptr && nearestRail != nullptr)
    {
        //check if connect nearest Rail
        QPoint testedPoint1 = nearestRail->getP0WorldLocation().toPoint();
        QPoint testedPoint2 = (nearestRail->getP0WorldLocation() + nearestRail->getP3RelativeLocation()).toPoint();
        int testedDistance1 = world->getWorldDistance(point, testedPoint1);
        int testedDistance2 = world->getWorldDistance(point, testedPoint2);

        if (testedDistance1 && testedDistance1 <= testedDistance2) nearestPoint = 0; //P0
        else if (testedDistance2 && testedDistance2 < testedDistance1) nearestPoint = 1; //P3
    }

    //check if rail is under construction or must be created
    if (actualRailConstructor->getOwnedRail() == nullptr) //not created yet
    {
        if (nearestRail != nullptr && nearestPoint != -1) createRailByStyle = 2;
        else createRailByStyle = 0;
    }
    else
    {
        if (nearestRail == nullptr || nearestPoint == -1) createRailByStyle = 1;
        else createRailByStyle = 3;
    }

    //choose creating style from previous condition (e.g. connected, lined, etc.)
    int zoomLevel = world->getWorldView()->getZoomLevel();
    switch (createRailByStyle)
    {
    case 0:
    {
        //create new lined rail and start constructing
        actualRailConstructor->actualizeConstructor(point, zoomLevel);
        actualRailConstructor->setOwnedRail(dynamic_cast<Rail*>(world->addActor(RAIL_ACTOR)));
        actualRailConstructor->underConstruction(true);
        break;
    }
    case 1:
    {
        //comnplete lined rail
        actualRailConstructor->actualizeConstructor(point, zoomLevel);
        Rail* createdRail = actualRailConstructor->getOwnedRail();
        world->getWorldCollide()->addCollideTriger(createdRail, SPHERE_COLLIDER, {RAIL_CHANNEL}, QPoint(0,0), 0.0f, 120); //for P0 point
        world->getWorldCollide()->addCollideTriger(createdRail, SPHERE_COLLIDER, {RAIL_CHANNEL}, createdRail->getP3RelativeLocation().toPoint(), 0.0f, 120);//for P3 point
        world->getWorldCollide()->addCollideTriger(createdRail, BOX_COLLIDER, {STATIC_CHANNEL},  QPoint(0,0), 0.0f, 1);//create object BoxCollider
        actualRailConstructor->getOwnedRail()->setRailObjectBoxCollider();
        actualRailConstructor->actualizeConstructor(point, zoomLevel); //duplicied due to P3 point actualize
        actualRailConstructor->getOwnedRail()->actualizeAreasPosition();
        actualRailConstructor->underConstruction(false);
        break;
    }
    case 2:
    {
        //create new béziere rail
        //re-calculate nearest trigger from nearest actor
        QPoint newPoint = nearestRail->getLocation();
        if (nearestPoint == 1) newPoint += nearestRail->getP3RelativeLocation().toPoint();
        actualRailConstructor->setConnectedRail(nearestRail);
        actualRailConstructor->actualizeConstructor(newPoint, zoomLevel);

        if (nearestRail->getConnectedRail(nearestPoint*2) != nullptr && nearestRail->getConnectedRail(nearestPoint*2+1) != nullptr) //connection 0/1 or 2/3
        {
            managerConsole->printToConsole("The rail has a junction already", RED_BOLD_COLOR, MIDDLE_DURATION);
            break;
        }

        //ADD RAIL ACTOR
        actualRailConstructor->setOwnedRail(dynamic_cast<Rail*>(world->addActor(RAIL_ACTOR)));
        actualRailConstructor->getOwnedRail()->setLocation(newPoint, true);
        actualRailConstructor->getOwnedRail()->setP0WorldLocation(newPoint);
        actualRailConstructor->getOwnedRail()->connectRails(nearestRail, true);
        actualRailConstructor->underConstruction(true);
        break;
    }
    case 3:
    {
        //complete béziere rail and connect to second (before created) rail
        Rail* createdRail = actualRailConstructor->getOwnedRail();
        if (createdRail == nearestRail || nearestRail->getConnection(createdRail) != -1) //try to connect self self-connect conected rail
        {
            managerConsole->printToConsole("You cannot create and connect rail here", RED_BOLD_COLOR, MIDDLE_DURATION);
            break;
        }
        QPoint newPoint = nearestRail->getLocation();
        if (nearestPoint == 1) newPoint += nearestRail->getP3RelativeLocation().toPoint();
        world->getWorldCollide()->addCollideTriger(createdRail, 0, {RAIL_CHANNEL}, {0,0}, 0.0f, 120); //for P0 point
        world->getWorldCollide()->addCollideTriger(createdRail, 0, {RAIL_CHANNEL}, createdRail->getP3RelativeLocation().toPoint(), 0.0f, 120);//for P3 point
        world->getWorldCollide()->addCollideTriger(createdRail, 1, {STATIC_CHANNEL}, {0,0}, 0.0f, 1);//create object BoxCollider
        actualRailConstructor->actualizeConstructor(newPoint, world->getWorldView()->getZoomLevel());
        actualRailConstructor->getOwnedRail()->connectRails(nearestRail, false);
        actualRailConstructor->smoothEndPoint();
        actualRailConstructor->getOwnedRail()->actualizeAreasPosition();
        actualRailConstructor->getOwnedRail()->setRailObjectBoxCollider();
        actualRailConstructor->underConstruction(false);
        break;
    }
    default: {}
    }
}

void mwlogic::constructSignal()
{
    if (world->addActor(SIGNAL_ACTOR) == nullptr)
    {
        managerConsole->printToConsole("Signal is not connected to any rail point, or rail end is occupied by another signal!", RED_BOLD_COLOR, LONG_DURATION);
    }
}

void mwlogic::constructTrain(QPoint point)
{
    QList<Actor*> actors = world->getActorsCollideInLocation({STATIC_CHANNEL}, point);
    if (actors.size() != 0)
    {
        for (auto actor : actors)
        {
            if (dynamic_cast<Portal*>(actor))
            {
                Portal *portal = dynamic_cast<Portal*>(actor);
                int portalRailEnd = portal->getConectedArea();
                Rail* portalOwnedRail = portal->getConnectedRail();

                Train* createdTrain = dynamic_cast<Train*>(world->addActor(TRAIN_ACTOR));
                bool trainDirection;
                (portalRailEnd == 0)? trainDirection = true : trainDirection = false;
                if (portalRailEnd == -1 || !createdTrain->teleportTrainToRail(portalOwnedRail, trainDirection))
                {
                    //false =rail is too short -> delete
                    world->deleteActor(createdTrain);
                }
            }
        }
    }
}

void mwlogic::trainSelect()
{
    Actor* actualConstructor = world->getActualConstructor();
    if (actualConstructor == nullptr || !dynamic_cast<TrainSelector*>(actualConstructor)) return;

    TrainSelector* trainSelector = dynamic_cast<TrainSelector*>(actualConstructor);

    QPoint point = actualConstructor->getLocation();
    QList<Actor*> actors = world->getActorsCollideInLocation({TRAIN_CHANNEL, RAIL_CHANNEL, STATIC_CHANNEL}, point);
    int nearestTrainDistance = 99999999;
    int nearestSignalDistance = 99999999;

    Train* selectedTrain = trainSelector->getSelectedTrain();
    Train* nearestTrain = trainSelector->getNearestTrain();

    if (selectedTrain == nullptr && nearestTrain != nullptr)
    {
       trainSelector->setSelectedTrain();
       menuSelected = TRAIN_MODE_SELECT_PATH;
       setTrainMenu(trainSelector->getSelectedTrain());
    }
}

void mwlogic::clickInTrainMenu()
{
    Actor* actualConstructor = world->getActualConstructor();
    if (actualConstructor == nullptr || !dynamic_cast<TrainSelector*>(actualConstructor)) return;
    TrainSelector* trainSelector = dynamic_cast<TrainSelector*>(actualConstructor);
    Train* selectedTrain = trainSelector->getSelectedTrain();
    if (selectedTrain->getIdle() && (menuSelected != TRAIN_MODE_LEAVE_TRAIN && menuSelected !=TRAIN_MODE_EXIT))
    {      
       managerConsole->printToConsole("The train is idle now. If you want to continue your journey, please start the train using the 'motor button", DEFAULT_COLOR, MIDDLE_DURATION);
       return;
    }
    switch (menuSelected)
    {
       case TRAIN_MODE_SELECT_PATH:
        {
           trainSelector->findPathToSignal(); //try to find a viable path to the selected signal (the selected signal is saved in TrainSelector)
           break;
        }
        case TRAIN_MODE_MOVE:
        {
            selectedTrain->setAutopilot(false);
            selectedTrain->recalculateRemainToPathEnd();
            selectedTrain->setTravelDistance(selectedTrain->getRemainToPathEnd());
            if (selectedTrain->getActualSpeed() == 0.0f) selectedTrain->setActualSpeed(1.0f);
            break;
        }
        case TRAIN_MODE_MOVE_VIA:
        {
            selectedTrain->setAutopilot(false);
            break;
        }
        case TRAIN_MODE_MOVE_TO:
        {
            selectedTrain->setAutopilot(false);
            break;
        }
        case TRAIN_MODE_AUTOPILOT:
        {
            selectedTrain->setAutopilot(true);
            selectedTrain->recalculateRemainToPathEnd();
            selectedTrain->setTravelDistance(selectedTrain->getRemainToPathEnd());
            if (selectedTrain->getRemainToPathEnd() > 50 && selectedTrain->getActualSpeed() == 0.0f) selectedTrain->setActualSpeed(1.0f);
            break;
        }
        case TRAIN_MODE_CHANGE_DIRECTION:
        {
            if (selectedTrain->getActualSpeed() == 0)
            {
                managerConsole->printToConsole("Train direction changed", DEFAULT_COLOR, MIDDLE_DURATION);
                selectedTrain->changeMoveDirection();
                TrainNavigation::checkSignalsOnPath(selectedTrain->getShunt(), selectedTrain->getActualRail(), selectedTrain->getRemainingPath(),selectedTrain->getDirectionToRailEnd(),selectedTrain->getRemainToPathEnd()- selectedTrain->getActualSpeed());
            }
            else managerConsole->printToConsole("Can´t change the direction of the train, because the train is moving now", DEFAULT_COLOR, MIDDLE_DURATION);
            break;
        }
        case TRAIN_MODE_CHANGE_MODE:
        {
            if (selectedTrain->getShunt())
            {
                selectedTrain->setShunt(false);
                setTrainMenu(selectedTrain);
                managerConsole->printToConsole("The train is in normal mode now", DEFAULT_COLOR, MIDDLE_DURATION);
            }
            else
            {
                selectedTrain->setShunt(true);
                setTrainMenu(selectedTrain);
                managerConsole->printToConsole("the train is in shunt mode now", DEFAULT_COLOR, MIDDLE_DURATION);
            }
            break;
        }
        case TRAIN_MODE_UNCOUPLE:
        {
            if (selectedTrain->getActualSpeed() == 0)
            {
                managerConsole->printToConsole("Temporarry solution - uncouple", DEFAULT_COLOR, MIDDLE_DURATION);
                selectedTrain->uncouple(1);
            }
            else managerConsole->printToConsole("Can´t uncouple now, because the train is moving now", DEFAULT_COLOR, MIDDLE_DURATION);
            break;
        }
        case TRAIN_MODE_COUPLE:
        {
            break;
        }
        case TRAIN_MODE_LOAD:
        {
            break;
        }
        case TRAIN_MODE_UNLOAD:
        {
            break;
        }
        case TRAIN_MODE_LEAVE_TRAIN:
        {
            if (selectedTrain->getActualSpeed() == 0.0f)
            {
                if (!selectedTrain->getIdle())
                {
                    selectedTrain->idle(true);
                    world->kickTickedActor(dynamic_cast<Actor*>(selectedTrain));
                    setTrainMenu(selectedTrain);
                }
                else
                {
                    selectedTrain->idle(false);
                    setTrainMenu(selectedTrain);
                    world->tickedActorsList.push_back(selectedTrain);
                }
            }
            else managerConsole->printToConsole("The train can´t idle now, because the train is moving now", DEFAULT_COLOR, MIDDLE_DURATION);
            break;
        }
        case TRAIN_MODE_EXIT:
        {
            qDebug() << "exit";
            selectedTrain->selectTrain(false);
            menuSelected = PLAY_SELECT_START;
            setPlaySelectInterface();
            break;
        }
        default: {}
        }

}

mwlogic::~mwlogic() {}
