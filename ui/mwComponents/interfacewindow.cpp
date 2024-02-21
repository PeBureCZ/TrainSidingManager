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
    playButSwitch(menuSelected >= PLAY_MODE_START && menuSelected <= PLAY_MODE_END);
}

void InterfaceWindow::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        if (menuSelected >= SELECT_EDIT_START && menuSelected <= EDIT_MODE_END)
        {
            //editor + EDIT/SELECT
            ActorConstructor* constructor = world->getActualConstructor();
            bool sharedBool = (constructor != nullptr && dynamic_cast<SelectConstructor*>(constructor));
            if (sharedBool)
            {
                SelectConstructor* selector = dynamic_cast<SelectConstructor*>(constructor);
                if (selector->getUnderSelect() == true)
                {
                    selector->setUnderEdit(true);
                    managerConsole->printToConsole("under edit = true", GREEN_COLOR, VERY_LONG_DURATION);
                }
            }
        }
        else if (menuSelected >= EDIT_MODE_START && menuSelected <= EDIT_ADD_END)
        {
            //editor + ADD
            switch (menuSelected)
            {
                //case 0: same as default
                case RAIL_ADD_MODE: //add Rail (RailConstructor)
                {
                    int xBarValue = world->getWorldView()->horizontalScrollBar()->value();
                    int yBarValue = world->getWorldView()->verticalScrollBar()->value();
                    int zoomLevel = world->getWorldView()->getZoomLevel();
                    constructRail(world->getRelativeWorldPos(event->pos(),xBarValue, yBarValue, zoomLevel));
                    break;
                }
                case PORTAL_ADD_MODE:
                {
                    world->addActor(PORTAL_ACTOR);
                    break;
                }
                case SIGNAL_ADD_MODE:
                    constructSignal();
                    break;
                default: {}break;//incl. 0
                    //nothing yet...;
            }
        }
        else if (menuSelected >= PLAY_MODE_START && menuSelected <= ADD_PLAY_END)
        {
            //playmode + ADD
            switch (menuSelected)
            {
                case PLAY_ADD_TRAIN:
                {
                    int xBarValue = world->getWorldView()->horizontalScrollBar()->value();
                    int yBarValue = world->getWorldView()->verticalScrollBar()->value();
                    int zoomLevel = world->getWorldView()->getZoomLevel();
                    constructTrain(world->getRelativeWorldPos(event->pos(),xBarValue, yBarValue, zoomLevel));
                    break;
                }
                default: {}
            }

        }
        else if (menuSelected >= SELECT_PLAY_START && menuSelected <= PLAY_MODE_END)
        {
            //playmode + EDIT/SELECT

        }
    }
    else if (event->button() == Qt::RightButton)
    {
        if (menuSelected >= menuSelected && menuSelected <= PORTAL_ADD_MODE)
        {
            world->deleteConstructor(true);
            menuSelected = EDIT_MODE_FREE;
        }
    }
}

void InterfaceWindow::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        if (menuSelected >= SELECT_EDIT_START && menuSelected <= EDIT_MODE_END)
        {
            leftMouseRelease();
        }
    }
    else if (event->button() == Qt::RightButton)
    {
        if (menuSelected >= SELECT_EDIT_START && menuSelected <= EDIT_MODE_END)
        {
            rightMouseRelease();
        }
    }
}

void InterfaceWindow::leftMouseRelease()
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
            managerConsole->printToConsole("under select = true", GREEN_COLOR, VERY_LONG_DURATION);
        }
        else if (selector->getUnderEdit() == true)
        {
            selector->setUnderEdit(false);
            managerConsole->printToConsole("under edit = false", GREEN_COLOR, VERY_LONG_DURATION);
        }
        else managerConsole->printToConsole("nothing", GREEN_COLOR, VERY_LONG_DURATION);
    }
}

void InterfaceWindow::rightMouseRelease()
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
            managerConsole->printToConsole("under select and edit = false", GREEN_COLOR, VERY_LONG_DURATION);
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
    else menuSelected = PLAY_MODE_FREE;
    mwlogic::playButSwitch(editMode);
}

void InterfaceWindow::selectMenuSwitch(bool selectMode)
{
    ConsoleTextsStruct console;
    if (menuSelected >= EDIT_MODE_START && menuSelected <= EDIT_MODE_END)
    {
        if (selectMode)
        {
            managerConsole->printToConsole("switch to select option in edit mode", YELLOW_BOLD_COLOR, 140);
            menuSelected = SELECT_EDIT_START;
        }
        else
        {
            managerConsole->printToConsole("Switch to add option in edit mode", YELLOW_BOLD_COLOR, 140);
            menuSelected = EDIT_MODE_FREE;
        }
    }
    else if(menuSelected >= PLAY_MODE_START && menuSelected <= PLAY_MODE_END)
    {
        if (selectMode)
        {
            managerConsole->printToConsole("switch to select option in play mode", YELLOW_BOLD_COLOR, 140);
            menuSelected = SELECT_PLAY_START;
        }
        else
        {
            managerConsole->printToConsole("switch to add option in play mode", YELLOW_BOLD_COLOR, 140);
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
    if (menuSelected == OPTION_MODE_START || (menuSelected >= EDIT_MODE_START && menuSelected <= EDIT_ADD_END))
    {
        menuSelected = RAIL_ADD_MODE; //if editMode -> constructiong Rail
        addConstructor(RAIL_CONSTRUCTOR);
    }
    else if (menuSelected >= SELECT_EDIT_START && menuSelected <= EDIT_MODE_END)
    {
        menuSelected = RAIL_SELECTOR_MODE;
        addConstructor(RAIL_SELECTOR);
    }
    else if (menuSelected >= PLAY_MODE_START && menuSelected <= ADD_PLAY_END)
    {
        menuSelected = PLAY_ADD_TRAIN;
    }
}

void InterfaceWindow::on_MultiFuncBut2_clicked()
{
    if (menuSelected == OPTION_MODE_START || (menuSelected >= EDIT_MODE_START && menuSelected <= EDIT_ADD_END))
    {
        menuSelected = SIGNAL_ADD_MODE; //if editMode -> constructiong signals
        addConstructor(SIGNAL_CONSTRUCTOR); //delete constructor included
    }
}

void InterfaceWindow::on_MultiFuncBut3_clicked()
{
    if (menuSelected == OPTION_MODE_START || (menuSelected >= EDIT_MODE_START && menuSelected <= EDIT_ADD_END))
    {
        menuSelected = PORTAL_ADD_MODE; //if editMode -> constructiong signals
        addConstructor(PORTAL_CONSTRUCTOR); //delete constructor included
    }
}

void InterfaceWindow::on_MultiFuncBut4_clicked()
{

}

void InterfaceWindow::on_MultiFuncBut5_clicked()
{

}

void InterfaceWindow::on_MultiFuncBut6_clicked()
{

}

void InterfaceWindow::on_MultiFuncBut7_clicked()
{

}

void InterfaceWindow::on_MultiFuncBut8_clicked()
{

}

void InterfaceWindow::on_MultiFuncBut9_clicked()
{

}

void InterfaceWindow::on_MultiFuncBut10_clicked()
{

}

void InterfaceWindow::on_MultiFuncBut11_clicked()
{

}

void InterfaceWindow::on_MultiFuncBut12_clicked()
{

}

void InterfaceWindow::on_MultiFuncBut13_clicked()
{

}

void InterfaceWindow::on_MultiFuncBut14_clicked()
{

}

void InterfaceWindow::on_MultiFuncBut15_clicked()
{

}

void InterfaceWindow::on_MultiFuncBut16_clicked()
{

}

void InterfaceWindow::on_MultiFuncBut17_clicked()
{

}

void InterfaceWindow::on_MultiFuncBut18_clicked()
{

}

void InterfaceWindow::on_MultiFuncBut19_clicked()
{

}

void InterfaceWindow::on_MultiFuncBut20_clicked()
{

}

void InterfaceWindow::on_MultiFuncBut21_clicked()
{

}

void InterfaceWindow::on_MultiFuncBut22_clicked()
{

}

void InterfaceWindow::on_MultiFuncBut23_clicked()
{

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
            managerConsole->printToConsole("Last item deleted", RED_COLOR, MIDDLE_DURATION);
        }
        else managerConsole->printToConsole("No item to delete", DEFAULT_COLOR, VERY_LONG_DURATION);
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
