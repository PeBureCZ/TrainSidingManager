#include "mainWindow/mwlogic.h"

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
    if (menuSelected == PLAY_MODE_FREE) elapsedTime += deltaTime;
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
    switch (constructorType)
    {
    case RAIL_CONSTRUCTOR:
        world->addRailConstructor();
        managerConsole->printToConsole("To place a track, click the left mouse button (LMB) on the surface. To delete, use the right mouse button (RMB)", 99, 500);
        managerConsole->printToConsole("(To connect to another track, use the left mouse button (LMB) near the end of another track)", 99, 500);
        break;
    case SIGNAL_CONSTRUCTOR:
        world->addSignalConstructor();
        managerConsole->printToConsole("To place a signal, move the mouse cursor closer to the breakpoints of one of the tracks. The track with the placed signal will be marked with a changed color", 99, 500);
        managerConsole->printToConsole("(To confirm the placement of a signal on the track, use the left mouse button (LMB))", 99, 500);
        break;
    case RAIL_SELECTOR:
        world->addRailSelector();
        managerConsole->printToConsole("For marking the track, click the left mouse button on the light blue highlighted track", 99, 500);
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
        actualRailConstructor->setOwnedRail(dynamic_cast<Rail*>(world->addRailwaylActor(1,point,nullptr)));
        actualRailConstructor->underConstruction(true);
        break;
    }
    case 1:
    {
        //comnplete lined rail
        actualRailConstructor->actualizeConstructor(point);
        Rail* createdRail = actualRailConstructor->getOwnedRail();
        world->getWorldCollide()->addTriggerToActor(createdRail, 0, {2}, {0,0}, 0.0f, 120); //for P0 point
        world->getWorldCollide()->addTriggerToActor(createdRail, 0, {2}, createdRail->getP3RelativeLocation().toPoint(), 0.0f, 120);//for P3 point
        world->getWorldCollide()->addTriggerToActor(createdRail, 1, {0}, {0,0}, 0.0f, 1);//create object BoxCollider
        actualRailConstructor->getOwnedRail()->setObjectBoxCollider();
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
        actualRailConstructor->setOwnedRail(dynamic_cast<Rail*>(world->addRailwaylActor(1,newPoint,nullptr)));
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
        world->getWorldCollide()->addTriggerToActor(createdRail, 0, {2}, {0,0}, 0.0f, 120); //for P0 point
        world->getWorldCollide()->addTriggerToActor(createdRail, 0, {2}, createdRail->getP3RelativeLocation().toPoint(), 0.0f, 120);//for P3 point
        world->getWorldCollide()->addTriggerToActor(createdRail, 1, {0}, {0,0}, 0.0f, 1);//create object BoxCollider
        actualRailConstructor->actualizeConstructor(newPoint);
        actualRailConstructor->getOwnedRail()->connectRails(nearestRail, false);
        actualRailConstructor->smoothEndPoint();
        actualRailConstructor->getOwnedRail()->actualizeAreasPosition();
        actualRailConstructor->getOwnedRail()->setObjectBoxCollider();
        actualRailConstructor->underConstruction(false);
        break;
    }
    default: {}
    }
}

void mwlogic::constructSignal()
{
    if (dynamic_cast<SignalConstructor*>(world->getActualConstructor()))
    {
        SignalConstructor* actualSignalConstructor = dynamic_cast<SignalConstructor*>(world->getActualConstructor());
        Rail* nearestRail = actualSignalConstructor->getNearestRail();
        if (nearestRail == nullptr) managerConsole->printToConsole("Signal is not connected to any rail!", 1, 500);
        else
        {
            int nearestEndArea = actualSignalConstructor->getNearestEndArea();
            if (nearestRail->getSignal(actualSignalConstructor->getNearestEndArea()) == nullptr)
            {
                managerConsole->printToConsole("Signal is not connected to any rail!", 1, 500);
            }
            world->addRailwaylActor(2, actualSignalConstructor->getLocation(), nearestRail); //create signal actor

        }

    }
}

mwlogic::~mwlogic() {}
