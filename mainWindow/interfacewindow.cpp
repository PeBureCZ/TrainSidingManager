#include "interfacewindow.h"

/*
    menuSelected:
    0-99 = menu option
    100-199 = edit mode functionss
    200-299 = play mode functions

    /*
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
    103 = spawn SignalConstructor and prepare to add Signal

    0-99 = menu option
    100-199 = edit mode functionss
    200-299 = play mode functions
    */

InterfaceWindow::InterfaceWindow(mwlogic *parent)
    : mwlogic{parent}
{}


void InterfaceWindow::on_TestButton1_clicked() //temporary
{
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
            case RAIL_SPAWN_MODE: //add Rail (RailConstructor)
                addConstructor(1, world->getRelativeWorldPos(event->pos()));
                break;
            case RAIL_ADD_MODE: //constructing rail (RailConstructor)
                constructRail(event->pos());
                break;
            default: break;//incl. 0
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
    else if(!editMode)
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
    if (menuSelected == EDIT_MODE) menuSelected = RAIL_SPAWN_MODE; //if editMode -> constructiong Rail
}

void InterfaceWindow::on_MultiFuncBut2_clicked()
{
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


