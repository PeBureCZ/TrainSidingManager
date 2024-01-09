#include "interfacewindow.h"

InterfaceWindow::InterfaceWindow(mwlogic *parent)
    : mwlogic{parent}
{}


void InterfaceWindow::on_TestButton1_clicked() //temporary
{
    menuSelected = NOT_USED_NOW;
}

void InterfaceWindow::on_PlayBut_clicked()
{
    playButSwitch(menuSelected == PLAY_MODE_FREE);
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
        case PLAY_MODE_FREE: //add Rail (constructor)
            //nothing?
            break;
        case RAIL_ADD_MODE: //constructing rail (RailConstructor)
            world->deleteConstructor(true);
            menuSelected = EDIT_MODE_FREE;
            break;
        case SIGNAL_ADD_MODE: //constructing signal (SignalConstructor)
            world->deleteConstructor(true);
            menuSelected = EDIT_MODE_FREE;
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
    if (editMode) menuSelected = EDIT_MODE_FREE;
    else
    {
        menuSelected = PLAY_MODE_FREE;
        if (world->railList.size() > 0) world->addTrainActor(world->railList[0]);
    }
    mwlogic::playButSwitch(editMode);
}

void InterfaceWindow::selectMenuSwitch(bool selectMode)
{
    if (menuSelected >= EDIT_MODE_START && menuSelected <= EDIT_MODE_END)
    {
        if (selectMode)
        {
            managerConsole->printToConsole("switch to select option in edit mode", 6, 140);
            menuSelected = SELECT_EDIT_START;
        }
        else
        {
            managerConsole->printToConsole("switch to add option in edit mode", 6, 140);
            menuSelected = EDIT_MODE_FREE;
        }
    }
    else if(menuSelected >= PLAY_MODE_START && menuSelected <= PLAY_MODE_END)
    {
        if (selectMode)
        {
            managerConsole->printToConsole("switch to select option in play mode", 6, 140);
            menuSelected = SELECT_PLAY_START;
        }
        else
        {
            managerConsole->printToConsole("switch to add option in play mode", 6, 140);
            menuSelected = PLAY_MODE_FREE;
        }
    }
    mwlogic::selectMenuSwitch(selectMode);
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
    if (menuSelected != PLAY_MODE_FREE)
    {
        //delete button
        menuSelected = EDIT_MODE_FREE;
        if (world->actorList.size() > 0)
        {
            //delete last created actor
            Actor* deletedActor = world->actorList[world->actorList.size()-1];
            if (world->getActualConstructor() != nullptr) world->deleteConstructor(true);
            else world->deleteActor(deletedActor);
            managerConsole->printToConsole("Last item deleted", 7, 160);
        }
        else managerConsole->printToConsole("No item to delete", 99, 400);
    }
}

void InterfaceWindow::on_AddMenuBut_clicked()
{
    selectMenuSwitch(false);
}


void InterfaceWindow::on_EditMenuBut_clicked()
{
    selectMenuSwitch(true);
}
