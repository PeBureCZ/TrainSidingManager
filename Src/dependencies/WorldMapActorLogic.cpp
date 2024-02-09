#include "WorldMapActorLogic.h"

Actor *WorldMap::addActor(int indexOfActor)
{
    if (indexOfActor > CONSTRUCTORS_START && indexOfActor < CONSTRUCTORS_END)
    {
        switch (indexOfActor)
        {
        case RAIL_CONSTRUCTOR:

            addRailConstructor();
            break;
        case SIGNAL_CONSTRUCTOR:
            addSignalConstructor();
            break;
        case RAIL_SELECTOR:
            addRailSelector();
            break;
        case PORTAL_CONSTRUCTOR:
            addPortalConstructor();
            break;
        default: {}
        }
    }
    else if(indexOfActor > STATIC_ACTORS_START && indexOfActor < STATIC_ACTORS_END)
    {

    }
    else if(indexOfActor > RAILWAY_ACTORS_START && indexOfActor < RAILWAY_ACTORS_END)
    {
        return addRailwaylActor(indexOfActor);
    }
    else if(indexOfActor > VEHICLE_ACTORS_START && indexOfActor < VEHICLE_ACTORS_END)
    {

    }
    else if(indexOfActor > SELECTORS_START && indexOfActor < SELECTORS_END)
    {

    }
    else return nullptr;
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
    addActorToLists(railConstructor);
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
    addActorToLists(signalConstructor);
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
    portalConstructor->setCallCollisionChannels({2});
    addActorToLists(portalConstructor);
    setConstructor(portalConstructor);
    return portalConstructor;
}

Actor *WorldMap::addRailSelector()
{
    //ADD GRAPHIC FOR SIGNAL_CONSTRUCTOR = NULL
    //ADD SELECTOR (CONSTRUCTOR)
    Actor* railSelector = new RailSelector(nullptr, nullptr, nullptr); //without acttor to construct
    railSelector->setCallCollisionChannels({0,2});
    addActorToLists(railSelector);
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

Actor *WorldMap::addVehicleActor(Train *ownerTrain, int indexOfVehicle)
{
    SpriteColection newSprite; //struct
    QGraphicsItem* vehicleGraphicsItem = nullptr;
    Vehicle* newVehicle = nullptr;
    switch (indexOfVehicle)
    {
    case TRAIN_CD730:
    {
        vehicleGraphicsItem = new QGraphicsPixmapItem(newSprite.getSprite(CD730_SPRITE)); //sprite from struct
        newVehicle = new CD730(nullptr, vehicleGraphicsItem);
        break;
    }
    case VAGON_EAS:
    {
        vehicleGraphicsItem = new QGraphicsPixmapItem(newSprite.getSprite(EAS_SPRITE)); //sprite from struct
        newVehicle = new Eas(nullptr, vehicleGraphicsItem);
        break;
    }
    //case x: ....
    default: {}
    }
    if (vehicleGraphicsItem != nullptr && newVehicle != nullptr)
    {
        worldScene->addItem(vehicleGraphicsItem);
        dynamic_cast<Train*>(ownerTrain)->addVehicle(newVehicle, vehicleGraphicsItem); //needed for destructor!
    }
    return newVehicle;
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

Actor *WorldMap::addTrainActor(Rail* spawnOnRail)
{
    if (railList.size() > 0)
    {
        SpriteColection newSprite; //struct
        QGraphicsItem* trainItem = new QGraphicsPixmapItem(newSprite.getSprite(EMPTY_SPRITE)); //sprite from struct
        Actor* newTrain = new Train(nullptr, trainItem, spawnOnRail);
        addVehicleActor(dynamic_cast<Train*>(newTrain), TRAIN_CD730);

        qDebug() << "spawn train - temporary solution";
        addActorToLists(newTrain);
        tickedActorsList.push_back(newTrain); //actor with tick update
        dynamic_cast<Train*>(newTrain)->setActualSpeed(1300); //centimeters/s

        dynamic_cast<Train*>(newTrain)->startAutopilot();
        return newTrain;
    }
    return nullptr;
}

Actor *WorldMap::addRailwaylActor(int indexOfActor ) //need to refract later!
{
    if (getActualConstructor() == nullptr) return nullptr;
    QPoint mapLocation = getActualConstructor()->getLocation();
    Actor* connectedRail;
    switch (indexOfActor)
    {
    case RAIL_ACTOR: //Rail
    {
        connectedRail = dynamic_cast<RailConstructor*>(getActualConstructor())->getConnectedRail();
        //ADD PATH FOR RAIL ACTOR = GRAPHIC ITEM
        QPainterPath path;
        path.cubicTo(0, 0, 0, 0, 0, 0); //deffault line -> will be changed immediately
        QGraphicsPathItem* pathItem = new QGraphicsPathItem(path); //add graphics
        pathItem->setPen(QPen(Qt::blue, 14));
        pathItem->setPos(mapLocation.toPointF());
        worldScene->addItem(pathItem);

        //ADD RAIL ACTOR
        Actor* railActor = new Rail(nullptr, pathItem); //add actor
        Rail* railDynamic = dynamic_cast<Rail*>(railActor);

        addActorToLists(railActor);
        if (connectedRail != nullptr) railDynamic->setLined(false); // = rail is connected, start as béziere
        railActor->setLocation(mapLocation, true);

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
    case SIGNAL_ACTOR : //Signal
    {
        //ADD GRAPHIC FOR SIGNAL
        SpriteColection newSprite;
        QPixmap pixmap;
        SignalConstructor* constructor = dynamic_cast<SignalConstructor*>(actualConstructor);
        Rail* connectedRail = constructor->getNearestRail();
        int nearestEndArea = constructor->getNearestEndArea();

        if (constructor->getNearestAreaGraphic() != nullptr) pixmap = newSprite.getSprite(RED_SIGNAL_SPRITE);
        else pixmap = newSprite.getSprite(NO_SIGNAL_SPRITE);

        QGraphicsItem* signalGraphic = new QGraphicsPixmapItem(pixmap); //sprite from struct
        worldScene->addItem(signalGraphic);

        //ADD SIGNAL ACTOR
        Actor* newSignal = new Signal(nullptr, signalGraphic);
        newSignal->setLocation(mapLocation, true);
        addActorToLists(newSignal);

        if (connectedRail != nullptr && (nearestEndArea == 0 || nearestEndArea == 1))
        {
            dynamic_cast<Rail*>(connectedRail)->addSignal(nearestEndArea, dynamic_cast<Signal*>(newSignal));
        }
        return newSignal;
    }
    case PORTAL_ACTOR:
    {

    }
    default:{}
    }
}
