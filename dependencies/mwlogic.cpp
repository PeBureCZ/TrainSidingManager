#include "dependencies/mwlogic.h"

mwlogic::mwlogic(MainWindow *parent)
    : MainWindow{parent}
{
    menuSelected = 0;
    playModeActualized = false;
    elapsedTime = 0;
    /*
    0 = editMode
    1 = add Rail (create constructor)
    2 = constructing rail (RailConstructor)
    3 = playMode
    */
}

void mwlogic::actualizeMap()
{
    if (menuSelected == 3)
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
    if (menuSelected == 3) elapsedTime += deltaTime;
}

void mwlogic::playButSwitch(bool editMode)
{
    MainWindow::playButSwitch(editMode);
    InterfaceSet(menuSelected);
}

void mwlogic::mouseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        switch (menuSelected)
        {
        //case 0: same as default
        case 1: //1 = add Rail (RailConstructor)
        {
            QPoint point = (world->getRelativeWorldPos(event->pos()));
            int zoom = world->getWorldView()->getZoomLevel();
            int maxRadius = 150;
            if (zoom > 0) maxRadius += zoom * 150; //increase radius on zoom in
            QVector<Actor*> actors = world->getActorUnderClick({2});
            if (actors.size() == 0)
            {
                world->addRailConstructor(point, nullptr);
                menuSelected = 2;
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
                    menuSelected = 2;
                }
            }
            break;
        }
        case 2: //2 = constructing rail (RailConstructor)
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
                menuSelected = 1;
            }
            else
            {
                for (int i = 0; i < actors.size(); ++i)
                {
                    if (dynamic_cast<Rail*>(actors[i]))
                    {
                        QPoint point = event->pos();
                        Actor* actor = actors[i];
                        Trigger* nearestTrigger = world->getNearestTriggerInRange(actor, world->getRelativeWorldPos(point), maxRadius);
                        actualRailConstructor->actualizeConstructor(actor->getLocation() + nearestTrigger->getRelativeLocation());
                        actualRailConstructor->getOwnedRail()->connectRails(dynamic_cast<Rail*>(actors[i]), false);
                        actualRailConstructor->smoothEndPoint();
                        dynamic_cast<RailConstructor*>(world->getActualConstructor())->setObjectBoxCollider(); //actualize
                        world->deleteConstructor(false);
                        menuSelected = 1;
                    }
                }
            }
        }
        default:  //incl. 0
        {
            //QVector<Actor*> actors = world->getActorUnderClick({0});
            //nothing yet...
        }
        }
    }
    else if (event->button() == Qt::RightButton)
    {
        switch (menuSelected)
        {
        case 1: //1 = add Rail (constructor)
        {
            //nothing?
            break;
        }
        case 2: //2 = constructing rail (RailConstructor)
        {
            world->deleteConstructor(true);
            menuSelected = 1;
            break;
        }
        default: {} //incl. 0 = default
        }
    }
}

mwlogic::~mwlogic() {}
