#include "interfacewindow.h"

InterfaceWindow::InterfaceWindow(mwlogic *parent)
    : mwlogic{parent}
{}


void InterfaceWindow::on_TestButton1_clicked() //temporary
{
    managerConsole->addToConsole("asdad");
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
    }
    else if(!editMode)
    {
        menuSelected = 3;
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


void InterfaceWindow::on_MoveBut_clicked()
{
    //menuSelected = 0;
}

void InterfaceWindow::on_MultiFuncBut1_clicked()
{
    if (menuSelected == 0) menuSelected = 1; //if editMode -> constructiong Rail
}
