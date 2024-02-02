#include "interfacewindow.h"

InterfaceWindow::InterfaceWindow(mwlogic *parent)
    : mwlogic{parent}
{}

/*
void InterfaceWindow::on_TestButton1_clicked() //temporary
{
    menuSelected = NOT_USED_NOW;
}*/

void InterfaceWindow::on_PlayBut_clicked()
{
    playButSwitch(menuSelected == PLAY_MODE_FREE);
}

void InterfaceWindow::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        if (menuSelected >= SELECT_EDIT_START && menuSelected <= EDIT_MODE_END)
        {
            ActorConstructor* constructor = world->getActualConstructor();
            bool sharedBool = (constructor != nullptr && dynamic_cast<SelectConstructor*>(constructor));
            if (sharedBool)
            {
                SelectConstructor* selector = dynamic_cast<SelectConstructor*>(constructor);
                if (selector->getUnderSelect() == true)
                {
                    selector->setUnderEdit(true);
                    managerConsole->printToConsole("under edit = true", 9, 600);
                }
            }
        }
        else //edit mode
        {
            switch (menuSelected)
            {
            //case 0: same as default
            case RAIL_ADD_MODE: //add Rail (RailConstructor)
            {
                int xBarValue = world->getWorldView()->horizontalScrollBar()->value();
                int yBarValue = world->getWorldView()->verticalScrollBar()->value();
                constructRail(world->getRelativeWorldPos(event->pos(),xBarValue, yBarValue));
                break;
            }
            case NOT_USED_NOW:
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

void InterfaceWindow::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        if (menuSelected >= SELECT_EDIT_START && menuSelected <= EDIT_MODE_END)
        {
            ActorConstructor* constructor = world->getActualConstructor();
            bool sharedBool = (constructor != nullptr && dynamic_cast<SelectConstructor*>(constructor));
            if (sharedBool)
            {
                SelectConstructor* selector = dynamic_cast<SelectConstructor*>(constructor);
                if (selector->getUnderSelect() == false)
                {

                    selector->setUnderSelect(true);
                    if (dynamic_cast<RailSelector*>(selector))
                    {
                        world->getWorldScene()->addItem(dynamic_cast<RailSelector*>(selector)->getP1VisualPoint());
                        world->getWorldScene()->addItem(dynamic_cast<RailSelector*>(selector)->getP2VisualPoint());
                    }
                    managerConsole->printToConsole("under select = true", 9, 600);

                }
                else if (selector->getUnderEdit() == true)
                {
                    selector->setUnderEdit(false);
                    managerConsole->printToConsole("under edit = false", 9, 600);
                }
                else managerConsole->printToConsole("nothing", 9, 600);

            }
        }
    }
    else if (event->button() == Qt::RightButton)
    {
        if (menuSelected >= SELECT_EDIT_START && menuSelected <= EDIT_MODE_END)
        {
            ActorConstructor* constructor = world->getActualConstructor();
            bool sharedBool = (constructor != nullptr && dynamic_cast<SelectConstructor*>(constructor));
            if (sharedBool)
            {
                SelectConstructor* selector = dynamic_cast<SelectConstructor*>(constructor);
                if (selector->getUnderSelect() == true)
                {
                    selector->setUnderSelect(false);
                    selector->setUnderEdit(false);
                    managerConsole->printToConsole("under select and edit = false", 9, 600);
                }
            }
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
    if (menuSelected == OPTION_MODE_START || (menuSelected >= 100 && menuSelected <= EDIT_ADD_END))
    {
        menuSelected = RAIL_ADD_MODE; //if editMode -> constructiong Rail
        addConstructor(RAIL_CONSTRUCTOR);
    }
    if (menuSelected >= SELECT_EDIT_START && menuSelected <= EDIT_MODE_END)
    {
        menuSelected = RAIL_SELECTOR_MODE;
        addConstructor(RAIL_SELECTOR);
    }
}

void InterfaceWindow::on_MultiFuncBut2_clicked()
{
    if (menuSelected == 0 || (menuSelected >= 100 && menuSelected <= 199))
    {
        menuSelected = SIGNAL_ADD_MODE; //if editMode -> constructiong signals
        addConstructor(SIGNAL_CONSTRUCTOR); //delete constructor included
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
