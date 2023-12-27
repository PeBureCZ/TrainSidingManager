#include "interfacewindow.h"

InterfaceWindow::InterfaceWindow(mwlogic *parent)
    : mwlogic{parent}
{}


void InterfaceWindow::on_TestButton1_clicked() //temporary
{
}

void InterfaceWindow::on_PlayBut_clicked()
{
    playButSwitch(menuSelected == 3);
}

void InterfaceWindow::mousePressEvent(QMouseEvent *event)
{
    mouseEvent(event);
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
        menuSelected = 0;
        managerConsole->printToConsole("switch to edit mode", 6, 140);
    }
    else if(!editMode)
    {
        menuSelected = 3;
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
    if (menuSelected == 0) menuSelected = 1; //if editMode -> constructiong Rail
}

void InterfaceWindow::on_MultiFuncBut2_clicked()
{
    //menuSelected = 0;
}

void InterfaceWindow::on_MultiFuncBut24_clicked()
{
    if (menuSelected != 3)
    {
        //delete button
        menuSelected = 0;
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


