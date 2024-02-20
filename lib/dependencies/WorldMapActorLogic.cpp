#include "WorldMapActorLogic.h"

Actor *WorldMap::addActor(int indexOfActor)
{
    Actor* actor = nullptr;
    if (indexOfActor > CONSTRUCTORS_START && indexOfActor < CONSTRUCTORS_END)
    {
        switch (indexOfActor)
        {
        case RAIL_CONSTRUCTOR:
            actor = addRailConstructor();
            break;
        case SIGNAL_CONSTRUCTOR:
            actor = addSignalConstructor();
            break;
        case PORTAL_CONSTRUCTOR:
            actor = addPortalConstructor();
            break;
        default: {}
        }
    }
    else if(indexOfActor > STATIC_ACTORS_START && indexOfActor < STATIC_ACTORS_END)
    {

    }
    else if(indexOfActor > RAILWAY_ACTORS_START && indexOfActor < RAILWAY_ACTORS_END)
    {
        if (getActualConstructor() == nullptr) return nullptr;
        QPoint mapLocation = getActualConstructor()->getLocation();
        switch (indexOfActor)
        {
            case RAIL_ACTOR:
            {
                actor = addRail(mapLocation);
                break;
            }
            case SIGNAL_ACTOR :
            {
                actor = addSignal(mapLocation);
                    break;
            }
            case PORTAL_ACTOR:
            {
                actor = addPortal(mapLocation);
                break;
            }
            default:{}
        }
    }
    else if(indexOfActor > VEHICLE_ACTORS_START && indexOfActor < VEHICLE_ACTORS_END)
    {
        if (indexOfActor == TRAIN_ACTOR)  actor = addTrain();
        else
        {
            //add vehicles only
            //need train selector / portal selector - not yet
        }
    }
    else if(indexOfActor > SELECTORS_START && indexOfActor < SELECTORS_END)
    {
        switch (indexOfActor)
        {
        case RAIL_SELECTOR:
            actor = addRailSelector();
            break;
        default: {}
        }
    }
    if (actor != nullptr) addActorToLists(actor);
    return actor;
}

Actor *WorldMap::addRailConstructor()
{
    //ADD CONSTRUCTOR ACTOR
    SpriteColection newSprite;
    QGraphicsItem* railGraphicItem = new QGraphicsPixmapItem(newSprite.getSprite(RAIL_SPRITE)); //sprite from struct
    worldScene->addItem(railGraphicItem);
    Actor* railConstructor = new RailConstructor(nullptr, railGraphicItem, nullptr); //add actor
    railConstructor->setCallCollisionChannels({0,2});
    //railConstructor->setLocation(mapLocation,true);
    setConstructor(railConstructor);
    return railConstructor;
}

Actor* WorldMap::addSignalConstructor()
{
    //ADD GRAPHIC FOR SIGNAL_CONSTRUCTOR
    SpriteColection newSprite;
    QGraphicsItem* signalConstructorGraphic = new QGraphicsPixmapItem(newSprite.getSprite(RED_SIGNAL_SPRITE));
    worldScene->addItem(signalConstructorGraphic);
    //ADD CONSTRUCTOR ACTOR
    Actor* signalConstructor = new SignalConstructor(nullptr, signalConstructorGraphic, nullptr); //without acttor to construct
    signalConstructor->setCallCollisionChannels({0,2}); //call collisions with rail ends and railObject(railConnectionChannel)
    setConstructor(signalConstructor);
    return signalConstructor;
}

Actor *WorldMap::addPortalConstructor()
{
    //ADD GRAPHIC FOR SIGNAL_CONSTRUCTOR
    SpriteColection newSprite;
    QGraphicsItem* portalConstructorGraphic = new QGraphicsPixmapItem(newSprite.getSprite(PORTAL_SPRITE));
    worldScene->addItem(portalConstructorGraphic);
    //ADD CONSTRUCTOR ACTOR
    Actor* portalConstructor = new PortalConstructor(nullptr, portalConstructorGraphic, nullptr);
    portalConstructor->setCallCollisionChannels({0,2});
    setConstructor(portalConstructor);
    return portalConstructor;
}

Actor *WorldMap::addRailSelector()
{
    //ADD GRAPHIC FOR SIGNAL_CONSTRUCTOR = NULL
    //ADD SELECTOR (CONSTRUCTOR)
    Actor* railSelector = new RailSelector(nullptr, nullptr, nullptr); //without acttor to construct
    railSelector->setCallCollisionChannels({0,2});
    setConstructor(railSelector);
    return railSelector;
}

Actor *WorldMap::addStaticlActor(QPoint spawnPos, int indexOfActor)
{
    switch (indexOfActor)
    {
    case 1:
    {
        //nothing yet
        break;
    }
    case 2:
    {
        //nothing yet
        break;
    }
    default:{}
    }
    return nullptr;
}

void *WorldMap::addVehicleActors(Train *ownerTrain, QList<int> indexOfVehicles)
{
    //VEHICLES ARE NOT ADDED TO ACTOR LIST!!!
    //(delete train ---> delete all vehicles)
    SpriteColection newSprite; //struct
    QList<Vehicle*> newVehicles = {};

    for (auto vehicleIndex : indexOfVehicles)
    {
        switch (vehicleIndex)
        {
        case LOCO_CD730:
        {
            QGraphicsItem* vehicleGraphicsItem = new QGraphicsPixmapItem(newSprite.getSprite(CD730_SPRITE));
            newVehicles.push_back(new CD730(nullptr, vehicleGraphicsItem));
            break;
        }
        case LOCO_CD753:
        {
            QGraphicsItem* vehicleGraphicsItem = new QGraphicsPixmapItem(newSprite.getSprite(CD753_SPRITE));
            newVehicles.push_back(new CD753(nullptr, vehicleGraphicsItem));
            break;
        }
        case VAGON_EAS:
        {
            QGraphicsItem* vehicleGraphicsItem = new QGraphicsPixmapItem(newSprite.getSprite(EAS_SPRITE));
            newVehicles.push_back(new Eas(nullptr, vehicleGraphicsItem));
            break;
        }
        case VAGON_ZAES:
        {
            QGraphicsItem* vehicleGraphicsItem = new QGraphicsPixmapItem(newSprite.getSprite(ZAES_SPRITE));
            newVehicles.push_back(new Zaes(nullptr, vehicleGraphicsItem));
            break;
        }
        //case x: ....
        default: {}
        }
    }

    if (newVehicles.size() != 0)
    {
        for (auto vehicle : newVehicles)
        {
            worldScene->addItem(vehicle->getGraphicItem());
        }
        dynamic_cast<Train*>(ownerTrain)->addMultipleVehicleToTrain(newVehicles);
    }
}

void WorldMap::addActorToLists(Actor* addedActor)
{
    actorList.push_back(addedActor);
    if (dynamic_cast<Rail*>(addedActor)) railList.push_back(dynamic_cast<Rail*>(addedActor));
}

void WorldMap::setActorLocation(QPoint newLocation, Actor* actor)
{
    actor->setLocation(newLocation, true);
}

void WorldMap::deleteActor(Actor *actor)
{
    if (dynamic_cast<Actor*>(actor))
    {
        if (actor->canRecieveCollision())
        {
            worldCollide->removeActorFromCollideLists(actor);
        }
        if (tickedActorsList.contains(actor)) tickedActorsList.remove(tickedActorsList.indexOf(actor));

        if (dynamic_cast<Rail*>(actor))
        {
            int railIndex = railList.indexOf(dynamic_cast<Rail*>(actor));
            railList.remove(railIndex); //actor will be deleted from actor List
        }
        int actorIndex = actorList.indexOf(actor);
        delete actorList[actorIndex];
        actorList.remove(actorIndex);
    }
}

void WorldMap::setConstructor(Actor * actor)
{
    actualConstructor = dynamic_cast<ActorConstructor*>(actor);
    tickedActorsList.push_back(actor);
}

void WorldMap:: deleteConstructor(bool deleteCreation) //if deleteCreation = true, delete actor in ActorConstructor too
{
    if (actualConstructor != nullptr && dynamic_cast<ActorConstructor*>(actualConstructor))
    {
        Actor* actorConstructed = dynamic_cast<ActorConstructor*>(actualConstructor)->getActorConstructing();
        if (deleteCreation && actorConstructed != nullptr) deleteActor(actorConstructed);
        deleteActor(actualConstructor);
    }
    actualConstructor = nullptr;
}

Actor *WorldMap::addTrain()
{
    if (railList.size() > 0)
    {
        SpriteColection newSprite;
        QGraphicsItem* trainItem = new QGraphicsPixmapItem(newSprite.getSprite(EMPTY_SPRITE)); //sprite from struct
        Actor* newTrain = new Train(nullptr, trainItem, dynamic_cast<Rail*>(railList[0]));

        QList<int> vehicles = {LOCO_CD753, VAGON_EAS, VAGON_EAS, VAGON_EAS, VAGON_EAS, VAGON_ZAES, VAGON_ZAES, VAGON_ZAES, VAGON_ZAES, VAGON_ZAES, VAGON_ZAES, VAGON_ZAES};
        addVehicleActors(dynamic_cast<Train*>(newTrain), vehicles);

        qDebug() << "spawn train - temporary solution";
        tickedActorsList.push_back(newTrain); //actor with tick update (for move function)
        dynamic_cast<Train*>(newTrain)->setActualSpeed(100); //centimeters/s

        dynamic_cast<Train*>(newTrain)->startAutopilot();

        //temporary
        newTrain->setLocation(dynamic_cast<Rail*>(railList[0])->getLocation(),true);

        return newTrain;
    }
    return nullptr;
}

Actor* WorldMap::addRail(QPoint point)
{
    Actor* connectedRail = dynamic_cast<RailConstructor*>(getActualConstructor())->getConnectedRail();
    //ADD PATH FOR RAIL ACTOR = GRAPHIC ITEM
    QPainterPath path;
    path.cubicTo(0, 0, 0, 0, 0, 0); //deffault line -> will be changed immediately
    QGraphicsPathItem* pathItem = new QGraphicsPathItem(path); //add graphics
    pathItem->setPen(QPen(Qt::blue, 14));
    pathItem->setPos(point.toPointF());
    worldScene->addItem(pathItem);

    //ADD RAIL ACTOR
    Actor* railActor = new Rail(nullptr, pathItem); //add actor
    Rail* railDynamic = dynamic_cast<Rail*>(railActor);
    if (connectedRail != nullptr) railDynamic->setLined(false); // = rail is connected, start as béziere
    railActor->setLocation(point, true);

    //ADD GRAPHIC AREA OF RAIL ENDS
    QPen pen;
    pen.setWidth(3);
    pen.setColor(Qt::red);
    QPainterPath rect;
    int size = railDynamic->getVisualAreaSize();
    rect.addRect(0, 0, size, size);
    QGraphicsItem* pathArea0 = new QGraphicsPathItem(rect);
    QGraphicsItem* pathArea1 = new QGraphicsPathItem(rect);
    dynamic_cast<QGraphicsPathItem*>(pathArea0)->setPen(pen);
    dynamic_cast<QGraphicsPathItem*>(pathArea1)->setPen(pen);
    railDynamic->createArea(0, pathArea0);
    railDynamic->createArea(1, pathArea1);
    railDynamic->setVisibilityOfArea(0,false, Qt::blue); //set to invisible
    railDynamic->setVisibilityOfArea(1,false, Qt::blue); //set to invisible
    worldScene->addItem(pathArea0);
    worldScene->addItem(pathArea1);
    return railActor;
}

Actor* WorldMap::addPortal(QPoint point)
{
    PortalConstructor* actualPortalConstructor = dynamic_cast<PortalConstructor*>(getActualConstructor());
    Rail* connectedRail = actualPortalConstructor->getNearestRail();
    if (connectedRail == nullptr) return nullptr;

    //ADD GRAPHIC
    SpriteColection newSprite;
    QGraphicsItem* portalGraphic = new QGraphicsPixmapItem(newSprite.getSprite(PORTAL_SPRITE));
    worldScene->addItem(portalGraphic);

    //ADD PORTAL ACTOR
    Actor* portalActor = new Portal(nullptr, portalGraphic); //add actor
    QPoint correctedLocation = actualPortalConstructor->getGraphicItem()->pos().toPoint();
    //location may not be the same as the location of graphic item! (if snapped to rail)
    portalActor->setLocation(correctedLocation - QPoint(24,24),false);
    portalActor->setGraphicLocation(correctedLocation);
    portalActor->actualizeGraphicLocation();
    dynamic_cast<Portal*>(portalActor)->setConnectedRail(connectedRail);

    return portalActor;
}

Actor* WorldMap::addSignal(QPoint point)
{
    SignalConstructor* actualSignalConstructor = dynamic_cast<SignalConstructor*>(getActualConstructor());
    int nearestEndArea = actualSignalConstructor->getNearestEndArea();
    Rail* connectedRail = actualSignalConstructor->getNearestRail();
    if (connectedRail == nullptr || nearestEndArea == -1) return nullptr;

    //ADD GRAPHIC FOR SIGNAL
    SpriteColection newSprite;
    QPixmap pixmap;
    SignalConstructor* constructor = dynamic_cast<SignalConstructor*>(actualConstructor);

    if (constructor->getNearestAreaGraphic() != nullptr) pixmap = newSprite.getSprite(RED_SIGNAL_SPRITE);
    else pixmap = newSprite.getSprite(NO_SIGNAL_SPRITE);

    QGraphicsItem* signalGraphic = new QGraphicsPixmapItem(pixmap); //sprite from struct
    worldScene->addItem(signalGraphic);

    //ADD SIGNAL ACTOR
    Actor* newSignal = new Signal(nullptr, signalGraphic);
    newSignal->setLocation(point, true);

    if (connectedRail != nullptr && (nearestEndArea == 0 || nearestEndArea == 1))
    {
        dynamic_cast<Rail*>(connectedRail)->addSignal(nearestEndArea, dynamic_cast<Signal*>(newSignal));
    }
    return newSignal;
}
