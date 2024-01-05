#include "interfacewindow.h"

/*
    menuSelected:
    0-99 = menu option
    100-199 = edit mode functionss
    200-299 = play mode functions
    */

InterfaceWindow::InterfaceWindow(mwlogic *parent)
    : mwlogic{parent}
{}


void InterfaceWindow::on_TestButton1_clicked() //temporary
{
    menuSelected = NOT_USED_NOW;
}

void InterfaceWindow::on_PlayBut_clicked()
{
    playButSwitch(menuSelected == PLAY_MODE);
}

void InterfaceWindow::mousePressEvent(QMouseEvent *event)
{
    //mouseEvent(event);
    if (event->button() == Qt::LeftButton)
    {
        switch (menuSelected)
        {
            //case 0: same as default
            case RAIL_ADD_MODE: //add Rail (RailConstructor)
                constructRail(world->getRelativeWorldPos(event->pos()));
                break;
            case NOT_USED_NOW: //constructing rail (RailConstructor)
            {

                QVector<Actor*> actors = world->getActorsCollideInLocation({0},  world->getWorldView()->getRelativeFromCursor());
                qDebug() << actors.size();
                qDebug() << "_______";
                if (actors.size() > 0) world->deleteActor(actors[0]);
                break;
            }
            case SIGNAL_ADD_MODE:
                constructSignal();
                break;
            default: {}break;//incl. 0
                //nothing yet...;
        }
    }
    else if (event->button() == Qt::RightButton)
    {
        switch (menuSelected)
        {
        case PLAY_MODE: //add Rail (constructor)
            //nothing?
            break;
        case RAIL_ADD_MODE: //constructing rail (RailConstructor)
            world->deleteConstructor(true);
            menuSelected = EDIT_MODE;
            break;
        case SIGNAL_ADD_MODE: //constructing signal (SignalConstructor)
            world->deleteConstructor(true);
            menuSelected = EDIT_MODE;
            break;
        default: break;//incl. 0 = default
        }
    }
}

void InterfaceWindow::wheelEvent(QWheelEvent *event)
{
    MainWindow::wheelEvent(event);
}

void InterfaceWindow::playButSwitch(bool editMode)
{
    mwlogic::playButSwitch(editMode);
    if (editMode)
    {
        menuSelected = EDIT_MODE;
        managerConsole->printToConsole("switch to edit mode", 6, 140);
    }
    else
    {
        menuSelected = PLAY_MODE;
        managerConsole->printToConsole("switch to play mode", 6, 140);
        if (world->railList.size() > 0)
        {
            world->addTrainActor(world->railList[0]);
        }
    }
}

void InterfaceWindow::on_SubBut_clicked()
{
    world->getWorldView()->zoomOut();
}

void InterfaceWindow::on_AddBut_clicked()
{
    world->getWorldView()->zoomIn(false); //false = sideways by mouse
}


void InterfaceWindow::on_MultiFuncBut1_clicked()
{
    if (menuSelected == 0 || (menuSelected >= 100 && menuSelected <= 199))
    {
        menuSelected = RAIL_ADD_MODE; //if editMode -> constructiong Rail
        world->deleteConstructor(true);
        addConstructor(1, world->getRelativeWorldPos({0,0}));
    }
}

void InterfaceWindow::on_MultiFuncBut2_clicked()
{
    if (menuSelected == 0 || (menuSelected >= 100 && menuSelected <= 199))
    {
        menuSelected = SIGNAL_ADD_MODE; //if editMode -> constructiong signals
        addConstructor(2, {0,0}); //delete constructor included
    }
}

void InterfaceWindow::on_MultiFuncBut24_clicked()
{
    if (menuSelected != PLAY_MODE)
    {
        //delete button
        menuSelected = EDIT_MODE;
        if (world->actorList.size() > 0)
        {
            //delete last created actor
            Actor* deletedActor = world->actorList[world->actorList.size()-1];
            if (dynamic_cast<ActorConstructor*>(deletedActor)) world->deleteConstructor(deletedActor);
            else world->deleteActor(deletedActor);
            managerConsole->printToConsole("Last item deleted", 7, 160);
        }
        else managerConsole->printToConsole("No item to delete", 99, 400);
    }
}
