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
        if (elapsedTime > 1000) //actualize play mode only one time per 1 second
        {
            world->updateWorld();
            elapsedTime -= 1000;
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
        managerConsole->printToConsole(console.messageText[RAIL_CONSOLE_TEXT1], DEFAULT_COLOR, LONG_DURATION);
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
    int maxRadius = 5;
    if (zoom > 0) maxRadius += zoom * 25; //increase "snap radius" derived from zoom
    int nearestPoint = -1;

    if (actualRailConstructor != nullptr && nearestRail != nullptr)
    {
        //check if connect nearest Rail
        QPoint testedPoint1 = nearestRail->getP0WorldLocation().toPoint();
        QPoint testedPoint2 = (nearestRail->getP0WorldLocation() + nearestRail->getP3RelativeLocation()).toPoint();
        int testedDistance1 = world->getWorldDistance(point, testedPoint1);
        int testedDistance2 = world->getWorldDistance(point, testedPoint2);
        if (maxRadius > testedDistance1 && testedDistance1 <= testedDistance2)
        {
            nearestPoint = 0; //P0 is finded
        }
        else if (maxRadius > testedDistance2 && testedDistance2 < testedDistance1)
        {
            nearestPoint = 1; //P3 is finded
        }
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
        managerConsole->printToConsole("Signal is not connected to any rail point!", RED_BOLD_COLOR, LONG_DURATION);
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
                Rail* portalOwnedRail = dynamic_cast<Portal*>(actor)->getConnectedRail();
                Train* createdTrain = dynamic_cast<Train*>(world->addActor(TRAIN_ACTOR));
                if (!createdTrain->teleportTrainToRail(portalOwnedRail))
                {
                    //false = train is too short -> delete
                    world->deleteActor(createdTrain);

                }
            }
        }
    }
}

void mwlogic::trainOrSignalSelect()
{
    Actor* actualConstructor = world->getActualConstructor();
    if (actualConstructor == nullptr || !dynamic_cast<TrainSelector*>(actualConstructor)) return;

    TrainSelector* trainSelector = dynamic_cast<TrainSelector*>(actualConstructor);
    QPoint point = actualConstructor->getLocation();
    QList<Actor*> actors = world->getActorsCollideInLocation({TRAIN_CHANNEL, RAIL_CHANNEL, STATIC_CHANNEL}, point);
    int nearestTrainDistance = 99999999;
    int nearestSignalDistance = 99999999;
    Train* nearestTrain = nullptr;
    Signal* nearestSignal = nullptr;
    for (auto actor : actors)
    {
        if (dynamic_cast<Train*>(actor))
        {
            int testedDistance = world->getWorldDistance(actor->getLocation(), point);
            if (nearestTrainDistance > testedDistance)
            {
                nearestTrainDistance = testedDistance;
                nearestTrain = dynamic_cast<Train*>(actor);
            }
        }
        else if (dynamic_cast<Rail*>(actor))
        {
            //try to find nearest signal (from picture location!)
            Rail* nearRail = dynamic_cast<Rail*>(actor);
            if (nearRail->getOccupied()) continue;

            int testedDistance = 99999999;

            int testedRailEnd = 0;
            while(testedRailEnd < 2)
            {
                if (nearRail->getSignal(testedRailEnd) != nullptr)
                {
                    testedDistance = world->getWorldDistance(point, nearRail->getSignal(testedRailEnd)->getLocation());
                    if (testedDistance < nearestSignalDistance)
                    {
                        nearestSignalDistance = testedDistance;
                        nearestSignal = nearRail->getSignal(testedRailEnd);
                    }
                }
                testedRailEnd++;
            }
        }
    }

    Train* selectedTrain = trainSelector->getSelectedTrain();
    if (nearestSignal != nullptr && trainSelector->getSelectedTrain() != nullptr)
    {
        qDebug() << "signal is near -> create new path";
        trainSelector->setSelectedSignal(nearestSignal);
        trainSelector->findPathToSignal(); //try to find a viable path to the selected signal (the selected signal is saved in TrainSelector)
        trainSelector->setSelectedSignal(nullptr);
    }
    else if (nearestSignal == nullptr && nearestTrain != nullptr)
    {
        qDebug() << "train selected";
        trainSelector->setSelectedTrain(nearestTrain);
    }
    else if (nearestSignal == nullptr)
    {
        qDebug() << "nothing / signal deselect";
        trainSelector->setSelectedSignal(nullptr);
    }

}

mwlogic::~mwlogic() {}
