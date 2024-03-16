#include "interfacewindow.h"

InterfaceWindow::InterfaceWindow(mwlogic *parent)
    : mwlogic{parent}
{}

void InterfaceWindow::on_PlayBut_clicked()
{
    playButSwitch(menuSelected >= PLAY_MODE_START && menuSelected <= PLAY_MODE_END);
}

void InterfaceWindow::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        if (menuSelected >= EDIT_SELECT_START && menuSelected <= EDIT_MODE_END)
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
                }
            }
        }
        else if (menuSelected >= EDIT_MODE_START && menuSelected <= EDIT_ADD_END)
        {
            //editor + ADD
            switch (menuSelected)
            {
                //case 0: same as default
                case RAIL_CONSTRUCT_MODE: //add Rail (RailConstructor)
                {
                    int xBarValue = world->getWorldView()->horizontalScrollBar()->value();
                    int yBarValue = world->getWorldView()->verticalScrollBar()->value();
                    int zoomLevel = world->getWorldView()->getZoomLevel();
                    constructRail(world->getRelativeWorldPos(event->pos(),xBarValue, yBarValue, zoomLevel));
                    break;
                }
                case PORTAL_CONSTRUCT_MODE:
                {
                    world->addActor(PORTAL_ACTOR);
                    break;
                }
                case SIGNAL_CONSTRUCT_MODE:
                    constructSignal();
                    break;
                default: {}break;//incl. 0
                    //nothing yet...;
            }
        }
        else if (menuSelected >= PLAY_MODE_START && menuSelected <= PLAY_ADD_END)
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
        else if (menuSelected >= PLAY_SELECT_START && menuSelected <= PLAY_MODE_END)
        {
            //playmode + EDIT/SELECT
            switch (menuSelected)
            {
                case TRAIN_MODE_SELECT_PATH:
                {
                    clickInTrainMenu();
                    break;
                }
                case PLAY_SELECT_TRAIN:
                {
                    trainSelect();
                    break;
                }
                default: {}
            }

        }
    }
    else if (event->button() == Qt::RightButton)
    {
        world->deleteConstructor();
        if (menuSelected <= EDIT_ADD_END) menuSelected = EDIT_MODE_START; //edit + add
        else if (menuSelected <= EDIT_MODE_END) menuSelected = EDIT_SELECT_START;// edit + select
        else if (menuSelected <= PLAY_ADD_END) menuSelected = PLAY_MODE_START;  // play + add
        else
        {
            menuSelected = PLAY_SELECT_START; // play + select
            setPlaySelectInterface();
        }
    }
}

void InterfaceWindow::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        if (menuSelected >= EDIT_SELECT_START && menuSelected <= EDIT_MODE_END)
        {
            leftMouseRelease();
        }
    }
    else if (event->button() == Qt::RightButton)
    {
        if (menuSelected >= EDIT_SELECT_START && menuSelected <= EDIT_MODE_END)
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
        }
        else if (selector->getUnderEdit() == true)
        {
            selector->setUnderEdit(false);
        }
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
        }
    }
}

void InterfaceWindow::wheelEvent(QWheelEvent *event)
{
    MainWindow::wheelEvent(event);
}

void InterfaceWindow::playButSwitch(bool editMode)
{
    world->deleteConstructor(); //have to be deleted before another actors!
    if (editMode)
    {
        menuSelected = EDIT_MODE_START;
        for (auto actorTicked : world->tickedActorsList)
        {
            world->deleteActor(actorTicked);
        }
    }
    else menuSelected = PLAY_MODE_START;
    mwlogic::playButSwitch(editMode);
}

void InterfaceWindow::selectMenuSwitch(bool selectMode)
{
    world->deleteConstructor();
    ConsoleTextsStruct console;
    if (menuSelected >= EDIT_MODE_START && menuSelected <= EDIT_MODE_END)
    {
        if (selectMode)
        {
            managerConsole->printToConsole("switch to select option in edit mode", YELLOW_BOLD_COLOR, 140);
            menuSelected = EDIT_SELECT_START;
        }
        else
        {
            managerConsole->printToConsole("Switch to add option in edit mode", YELLOW_BOLD_COLOR, 140);
            menuSelected = EDIT_MODE_START;
        }
    }
    else if(menuSelected >= PLAY_MODE_START && menuSelected <= PLAY_MODE_END)
    {
        if (selectMode)
        {
            managerConsole->printToConsole("switch to select option in play mode", YELLOW_BOLD_COLOR, 140);
            menuSelected = PLAY_SELECT_START;
        }
        else
        {
            managerConsole->printToConsole("switch to add option in play mode", YELLOW_BOLD_COLOR, 140);
            menuSelected = PLAY_MODE_START;
        }
    }
    mwlogic::selectMenuSwitch(selectMode);
}

void InterfaceWindow::on_ZoomSubBut_clicked()
{
    world->getWorldView()->zoomOut();
}

void InterfaceWindow::on_ZoomAddBut_clicked()
{
    world->getWorldView()->zoomIn(false); //false = sideways by mouse
}

void InterfaceWindow::on_MultiFuncBut1_clicked()
{
    if (menuSelected >= EDIT_MODE_START && menuSelected <= EDIT_ADD_END)
    {
        menuSelected = RAIL_CONSTRUCT_MODE; //if editMode -> constructiong Rail
        addConstructor(RAIL_CONSTRUCTOR);
    }
    else if (menuSelected >= EDIT_SELECT_START && menuSelected <= EDIT_MODE_END)
    {
        menuSelected = EDIT_SELECT_RAIL;
        addConstructor(RAIL_SELECTOR);
    }
    else if (menuSelected >= PLAY_MODE_START && menuSelected <= PLAY_ADD_END)
    {
        menuSelected = PLAY_ADD_TRAIN;
    }
    else if (menuSelected >= PLAY_SELECT_START && menuSelected <= PLAY_MODE_END)
    {
        if (menuSelected >= TRAIN_MODE_SELECT_PATH && menuSelected <= TRAIN_MODE_EXIT)
        {
            menuSelected = TRAIN_MODE_SELECT_PATH;
        }
        else if (menuSelected == PLAY_SELECT_START)
        {
            menuSelected = PLAY_SELECT_TRAIN;
            addConstructor(TRAIN_SELECTOR);
        }
    }
}

void InterfaceWindow::on_MultiFuncBut2_clicked()
{
    if (menuSelected >= EDIT_MODE_START && menuSelected <= EDIT_ADD_END)
    {
        menuSelected = SIGNAL_CONSTRUCT_MODE; //if editMode -> constructiong signals
        addConstructor(SIGNAL_CONSTRUCTOR); //delete constructor included
    }
    else if (menuSelected >= TRAIN_MODE_SELECT_PATH && menuSelected <= TRAIN_MODE_EXIT)
    {
        menuSelected = TRAIN_MODE_CHANGE_MODE; //shunt / normal mode
        clickInTrainMenu();
    }
}

void InterfaceWindow::on_MultiFuncBut3_clicked()
{
    if (menuSelected >= EDIT_MODE_START && menuSelected <= EDIT_ADD_END)
    {
        menuSelected = PORTAL_CONSTRUCT_MODE; //if editMode -> constructiong signals
        addConstructor(PORTAL_CONSTRUCTOR); //delete constructor included
    }
}

void InterfaceWindow::on_MultiFuncBut4_clicked()
{
    if (menuSelected >= TRAIN_MODE_SELECT_PATH && menuSelected <= TRAIN_MODE_EXIT)
    {
        menuSelected = TRAIN_MODE_AUTOPILOT;
        clickInTrainMenu();
    }
}

void InterfaceWindow::on_MultiFuncBut5_clicked()
{

}

void InterfaceWindow::on_MultiFuncBut6_clicked()
{
    if (menuSelected >= TRAIN_MODE_SELECT_PATH && menuSelected <= TRAIN_MODE_EXIT)
    {
        menuSelected = TRAIN_MODE_MOVE;
        clickInTrainMenu();
    }
}

void InterfaceWindow::on_MultiFuncBut7_clicked()
{
    if (menuSelected >= TRAIN_MODE_SELECT_PATH && menuSelected <= TRAIN_MODE_EXIT)
    {
        //load train
    }
}

void InterfaceWindow::on_MultiFuncBut8_clicked()
{
    if (menuSelected >= TRAIN_MODE_SELECT_PATH && menuSelected <= TRAIN_MODE_EXIT)
    {
        //unload train
    }
}

void InterfaceWindow::on_MultiFuncBut9_clicked()
{
    if (menuSelected >= TRAIN_MODE_SELECT_PATH && menuSelected <= TRAIN_MODE_EXIT)
    {
        menuSelected = TRAIN_MODE_UNCOUPLE;
        clickInTrainMenu();
    }
}

void InterfaceWindow::on_MultiFuncBut10_clicked()
{
    if (menuSelected >= TRAIN_MODE_SELECT_PATH && menuSelected <= TRAIN_MODE_EXIT)
    {
        menuSelected = TRAIN_MODE_COUPLE;
        clickInTrainMenu();
    }
}

void InterfaceWindow::on_MultiFuncBut11_clicked()
{
    if (menuSelected >= TRAIN_MODE_SELECT_PATH && menuSelected <= TRAIN_MODE_EXIT)
    {
        int savedMenuValue = menuSelected;
        menuSelected = TRAIN_MODE_LEAVE_TRAIN;
        clickInTrainMenu(); //if leave train -> menuSelected changed in function
        if (menuSelected == TRAIN_MODE_LEAVE_TRAIN) menuSelected = savedMenuValue;
    }
}

void InterfaceWindow::on_MultiFuncBut12_clicked()
{
    if (menuSelected >= TRAIN_MODE_SELECT_PATH && menuSelected <= TRAIN_MODE_EXIT)
    {
        int savedMenuValue = menuSelected;
        menuSelected = TRAIN_MODE_CHANGE_DIRECTION;
        clickInTrainMenu();
        menuSelected = savedMenuValue;
    }
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
    if (menuSelected >= EDIT_MODE_START && menuSelected <= EDIT_ADD_END)
    {
        //delete button
        menuSelected = EDIT_MODE_START;
        if (world->actorList.size() > 0)
        {
            //delete last created actor
            Actor* deletedActor = world->actorList[world->actorList.size()-1];
            if (world->getActualConstructor() != nullptr) world->deleteConstructor();
            else world->deleteActor(deletedActor);
            managerConsole->printToConsole("Last item deleted", RED_COLOR, MIDDLE_DURATION);
        }
        else managerConsole->printToConsole("No item to delete", DEFAULT_COLOR, VERY_LONG_DURATION);
    }
    else if (menuSelected >= TRAIN_MODE_SELECT_PATH && menuSelected <= TRAIN_MODE_EXIT) //TRAIN_MODE
    {
        menuSelected = TRAIN_MODE_EXIT;
        clickInTrainMenu();
    }
    else if (menuSelected != PLAY_MODE_START)
    {
        //edit mode + select
        //delete button
        menuSelected = EDIT_SELECT_START;
        if (world->actorList.size() > 0)
        {
            if (world->getActualConstructor() != nullptr && dynamic_cast<SelectConstructor*>(world->getActualConstructor()))
            {
                Actor* deletedActor = dynamic_cast<SelectConstructor*>(world->getActualConstructor())->getSelectedActor();
                if (deletedActor != nullptr)
                {
                    //the selector has to have the "getSelectedActor()" function
                    world->deleteConstructor();
                    world->deleteActor(deletedActor);
                    managerConsole->printToConsole("Last item deleted", RED_COLOR, MIDDLE_DURATION);
                }
            }
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
