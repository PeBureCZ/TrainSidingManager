#include "mwComponents/mwlogic.h"

mwlogic::mwlogic(MainWindow *parent)
    : MainWindow{parent}
{
    menuSelected = EDIT_MODE_FREE;
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
    world->deleteConstructor(true);
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
        //constructing béziere rail or near ends of exist rail or combinated

        //check if connect nearest Rail
        Rail* testedRail = dynamic_cast<Rail*>(actualRailConstructor->getNearestRail());
        QPoint testedPoint1 = testedRail->getP0WorldLocation().toPoint();
        QPoint testedPoint2 = (testedRail->getP0WorldLocation() + testedRail->getP3RelativeLocation()).toPoint();
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
    switch (createRailByStyle)
    {
    case 0:
    {
        //create new lined rail and start constructing
        actualRailConstructor->actualizeConstructor(point);
        actualRailConstructor->setOwnedRail(dynamic_cast<Rail*>(world->addActor(RAIL_ACTOR)));
        actualRailConstructor->underConstruction(true);
        break;
    }
    case 1:
    {
        //comnplete lined rail
        actualRailConstructor->actualizeConstructor(point);
        Rail* createdRail = actualRailConstructor->getOwnedRail();
        world->getWorldCollide()->addCollideTriger(createdRail, SPHERE_COLLIDER, {RAIL_CHANNEL}, QPoint(0,0), 0.0f, 120); //for P0 point
        world->getWorldCollide()->addCollideTriger(createdRail, SPHERE_COLLIDER, {RAIL_CHANNEL}, createdRail->getP3RelativeLocation().toPoint(), 0.0f, 120);//for P3 point
        world->getWorldCollide()->addCollideTriger(createdRail, BOX_COLLIDER, {STATIC_CHANNEL},  QPoint(0,0), 0.0f, 1);//create object BoxCollider
        actualRailConstructor->getOwnedRail()->setRailObjectBoxCollider();
        actualRailConstructor->actualizeConstructor(point); //duplicied due to P3 point actualize
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
        actualRailConstructor->actualizeConstructor(newPoint);

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
        QPoint newPoint = nearestRail->getLocation();
        if (nearestPoint == 1) newPoint += nearestRail->getP3RelativeLocation().toPoint();
        world->getWorldCollide()->addCollideTriger(createdRail, 0, {RAIL_CHANNEL}, {0,0}, 0.0f, 120); //for P0 point
        world->getWorldCollide()->addCollideTriger(createdRail, 0, {RAIL_CHANNEL}, createdRail->getP3RelativeLocation().toPoint(), 0.0f, 120);//for P3 point
        world->getWorldCollide()->addCollideTriger(createdRail, 1, {STATIC_CHANNEL}, {0,0}, 0.0f, 1);//create object BoxCollider
        actualRailConstructor->actualizeConstructor(newPoint);
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

void mwlogic::selectTrain(QPoint point)
{
    QList<Actor*> actors = world->getActorsCollideInLocation({TRAIN_CHANNEL}, point);
    int nearestTrainDistance = 99999999;
    Train* nearestTrain = nullptr;
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
    }
    if (nearestTrain != nullptr)
    {
        //create train selector!
    }

}

mwlogic::~mwlogic() {}
