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

    OLD
    0 = editMode
    1 = prepare to add constructor (e.g. SignalConstructor)
    2 = under constructing (e.g. RailConstructor)
    3 = playMode

    NEW
    0 = editMode
    1 = playMode

    100 = free
    101 = prepare to add rail constructor
    102 = under constructing rail
    103 = spawn SignalConstructor and prepare to add Signals

    0-99 = menu option
    100-199 = edit mode functionss
    200-299 = play mode functions

    #define EDIT_MODE 0
    #define PLAY_MODE 1
    #define FREE_MODE 100
    #define RAIL_SPAWN_MODE 101
    #define RAIL_ADD_MODE 102
    #define SIGNAL_ADD_MODE 103
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
    QVector<Actor*> actors = world->getActorUnderClick({2});
    if (actors.size() == 0)
    {
        switch (constructorType)
        {
        case 1: //1 = add Rail (RailConstructor)
            world->addRailConstructor(point, nullptr);
            managerConsole->printToConsole("To place a track, click the left mouse button (LMB) on the surface. To delete, use the right mouse button (RMB).", 99, 500);
            managerConsole->printToConsole("(To connect to another track, use the left mouse button (LMB) near the end of another track)", 99, 500);
            menuSelected = RAIL_ADD_MODE; //set menu "under constructor
            break;
        case 2:
            world->addSignalConstructor(point);
            managerConsole->printToConsole("To place a signal, move the mouse cursor closer to the breakpoints of one of the tracks. The track with the placed signal will be marked with a changed color", 99, 500);
            managerConsole->printToConsole("(To confirm the placement of a signal on the track, use the left mouse button (LMB))", 99, 500);
        default: {}
        }
    }
    else
    {
        Actor* nearestActor = nullptr;
        int distance = 99999999;
        for (int i = 0; i < actors.size(); i++)
        {
            Trigger* nearestTrigger = {};
            if (dynamic_cast<Rail*>(actors[i]))
            {
                nearestTrigger = world->getNearestTriggerInRange(actors[i], point, maxRadius);
                if (nearestTrigger == nullptr) continue; //all triggers are out of range
                int testedDistance = world->getDistance(nearestTrigger->getRelativeLocation() + dynamic_cast<Actor*>(actors[i])->getLocation(), point);
                if (distance > testedDistance) //nearest actor by trigger
                {
                    nearestActor = actors[i];
                    distance = testedDistance;
                }
            }
        }
        if (nearestActor != nullptr) //all actors are out of range
        {
            Trigger* nearestTrigger = world->getNearestTriggerInRange(nearestActor, point, maxRadius);
            world->addRailConstructor(nearestActor->getLocation() + nearestTrigger->getRelativeLocation(), dynamic_cast<Rail*>(nearestActor));
            menuSelected = RAIL_ADD_MODE;
        }
    }
}

void mwlogic::constructRail(QPoint point)
{
    QVector<Actor*> actors = world->getActorUnderClick({2});
    RailConstructor* actualRailConstructor = dynamic_cast<RailConstructor*>(world->getActualConstructor());
    Rail* createdRail = dynamic_cast<Rail*>(actualRailConstructor->getActorConstructing());

    //bug exception (connect self connected Rail)
    for (auto actor : actors)
    {
        if (dynamic_cast<Rail*>(actor) && -1 != dynamic_cast<Rail*>(actor)->getConnection(createdRail)) return;
        //true = Rail construction continue with actual Constructor
    }

    int zoom = world->getWorldView()->getZoomLevel();
    int maxRadius = 40;
    if (zoom > 0) maxRadius += zoom * 15; //increase radius on zoom in
    world->getWorldCollide()->addTriggerToActor(createdRail, 0, {2}, {0,0}, 0.0f); //for P0 point
    world->getWorldCollide()->addTriggerToActor(createdRail, 0, {2}, createdRail->getP3RelativeLocation().toPoint(), 0.0f);//for P3 point
    world->getWorldCollide()->addTriggerToActor(createdRail, 1, {0}, {0,0}, 0.0f);//create object BoxCollider
    if (actors.size() == 0)
    {
        actualRailConstructor->setObjectBoxCollider();
        world->deleteConstructor(false);
        menuSelected = RAIL_SPAWN_MODE;
    }
    else
    {
        for (int i = 0; i < actors.size(); ++i)
        {
            if (dynamic_cast<Rail*>(actors[i]))
            {
                Actor* actor = actors[i];
                Trigger* nearestTrigger = world->getNearestTriggerInRange(actor, world->getRelativeWorldPos(point), maxRadius);
                actualRailConstructor->actualizeConstructor(actor->getLocation() + nearestTrigger->getRelativeLocation());
                actualRailConstructor->getOwnedRail()->connectRails(dynamic_cast<Rail*>(actors[i]), false);
                actualRailConstructor->smoothEndPoint();
                dynamic_cast<RailConstructor*>(world->getActualConstructor())->setObjectBoxCollider(); //actualize
                world->deleteConstructor(false);
                menuSelected = RAIL_SPAWN_MODE;
            }
        }
    }
}

void mwlogic::constructSignal()
{
    if (dynamic_cast<SignalConstructor*>(world->getActualConstructor()))
    {
        SignalConstructor* actualSignalConstructor = dynamic_cast<SignalConstructor*>(world->getActualConstructor());
        world->addRailwaylActor(2, actualSignalConstructor->getLocation(), nullptr); //create signal actor
    }
}

mwlogic::~mwlogic() {}
