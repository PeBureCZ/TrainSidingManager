#include "mainWindow/mwlogic.h"

mwlogic::mwlogic(MainWindow *parent)
    : MainWindow{parent}
{
    menuSelected = EDIT_MODE;
    playModeActualized = false;
    elapsedTime = 0;
    /*
    menuSelected:
    FOR #define values: "mwlogic.h"
    0-99 = menu option
    100-199 = edit mode functionss
    200-299 = play mode functions
    */
}


void mwlogic::actualizeMap()
{
    if (menuSelected == PLAY_MODE)
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
    if (menuSelected == PLAY_MODE) elapsedTime += deltaTime;
}

void mwlogic::playButSwitch(bool editMode)
{
    MainWindow::playButSwitch(editMode);
    InterfaceSet(menuSelected);
}

void mwlogic::addConstructor(int constructorType, QPoint point)
{
    world->deleteConstructor(true);
    int zoom = world->getWorldView()->getZoomLevel();
    int maxRadius = 150;
    if (zoom > 0) maxRadius += zoom * 150; //increase radius on zoom in
    QVector<Actor*> actors = world->getActorsCollideInLocation({2}, world->getWorldView()->getRelativeFromCursor());
    switch (constructorType)
    {
    case 1: //1 = add Rail (RailConstructor)
        world->addRailConstructor(point, nullptr);
        managerConsole->printToConsole("To place a track, click the left mouse button (LMB) on the surface. To delete, use the right mouse button (RMB).", 99, 500);
        managerConsole->printToConsole("(To connect to another track, use the left mouse button (LMB) near the end of another track)", 99, 500);
        break;
    case 2:
        world->addSignalConstructor(point);
        managerConsole->printToConsole("To place a signal, move the mouse cursor closer to the breakpoints of one of the tracks. The track with the placed signal will be marked with a changed color", 99, 500);
        managerConsole->printToConsole("(To confirm the placement of a signal on the track, use the left mouse button (LMB))", 99, 500);
    default: {}
    }
}

void mwlogic::constructRail(QPoint point)
{
    QVector<Actor*> actors = world->getActorsCollideInLocation({2},world->getWorldView()->getRelativeFromCursor());
    RailConstructor* actualRailConstructor = dynamic_cast<RailConstructor*>(world->getActualConstructor());
    Actor* nearestActor = nullptr;
    Trigger* testedTrigger = nullptr;
    Trigger* nearestTrigger = nullptr;

    int createRailByStyle = -1;
    int zoom = world->getWorldView()->getZoomLevel();
    int maxRadius = 5;
    if (zoom > 0) maxRadius += zoom * 20; //increase radius on zoom

    if (actors.size() == 0 && actualRailConstructor != nullptr)
    {
        //constructing lined rail
        if (actualRailConstructor->getOwnedRail() == nullptr) createRailByStyle = 0;
        else createRailByStyle = 1;
    }
    else if (createRailByStyle == -1 && actualRailConstructor != nullptr)
    {
        //constructing béziere rail or near ends of exist rail or combinated
        int distance = 99999999;
        int testedDistance = 99999998;
        for (int i = 0; i < actors.size(); i++)
        {
            if (dynamic_cast<Rail*>(actors[i]))
            {
                testedTrigger = world->getNearestTriggerInRange(actors[i], point, maxRadius);
                if (testedTrigger != nullptr) //all triggers are out of range?
                {
                    testedDistance = world->getWorldDistance(testedTrigger->getRelativeLocation() + dynamic_cast<Actor*>(actors[i])->getLocation(), point);
                    if (testedDistance < distance) //nearest actor by trigger
                    {
                        nearestTrigger = testedTrigger;
                        nearestActor = actors[i];
                        distance = testedDistance;
                    }
                }
            }
        }
        if (actualRailConstructor->getOwnedRail() == nullptr)
        {
            if (nearestActor != nullptr && nearestTrigger != nullptr) createRailByStyle = 2;
            else createRailByStyle = 0;
        }
        else
        {
            if (nearestActor == nullptr || nearestTrigger == nullptr) createRailByStyle = 1;
            else createRailByStyle = 3;
        }
    }
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
            actualRailConstructor->setObjectBoxCollider();
            actualRailConstructor->actualizeConstructor(point); //duplicied due to P3 point actualize
            actualRailConstructor->getOwnedRail()->actualizeAreasPosition();
            actualRailConstructor->underConstruction(false);
            break;
        }
        case 2:
        {
            //create new béziere rail
            //re-calculate nearest trigger from nearest actor
            nearestTrigger = world->getNearestTriggerInRange(nearestActor, point, maxRadius);
            QPoint newPoint = nearestActor->getLocation() + nearestTrigger->getRelativeLocation();
            actualRailConstructor->setConnectedRail(dynamic_cast<Rail*>(nearestActor));
            actualRailConstructor->actualizeConstructor(newPoint);

            //ADD RAIL ACTOR
            actualRailConstructor->setOwnedRail(dynamic_cast<Rail*>(world->addRailwaylActor(1,newPoint,nullptr)));
            actualRailConstructor->getOwnedRail()->setLocation(newPoint, true);
            actualRailConstructor->getOwnedRail()->connectRails(dynamic_cast<Rail*>(nearestActor), true);
            actualRailConstructor->underConstruction(true);
            break;
        }
        case 3:
        {
            //complete béziere rail and connect to second (before created) rail
            Rail* createdRail = actualRailConstructor->getOwnedRail();
            QPoint newPoint = nearestActor->getLocation() + nearestTrigger->getRelativeLocation();
            world->getWorldCollide()->addTriggerToActor(createdRail, 0, {2}, {0,0}, 0.0f, 120); //for P0 point
            world->getWorldCollide()->addTriggerToActor(createdRail, 0, {2}, createdRail->getP3RelativeLocation().toPoint(), 0.0f, 120);//for P3 point
            world->getWorldCollide()->addTriggerToActor(createdRail, 1, {0}, {0,0}, 0.0f, 1);//create object BoxCollider
            actualRailConstructor->actualizeConstructor(newPoint);
            actualRailConstructor->getOwnedRail()->connectRails(dynamic_cast<Rail*>(nearestActor), false);
            actualRailConstructor->smoothEndPoint();
            actualRailConstructor->getOwnedRail()->actualizeAreasPosition();
            actualRailConstructor->setObjectBoxCollider();
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
        if (!actualSignalConstructor->holdRail()) managerConsole->printToConsole("Signal is not connected to any rail!", 1, 500);

        world->addRailwaylActor(2, actualSignalConstructor->getLocation(), nullptr); //create signal actor
    }
}

mwlogic::~mwlogic() {}
