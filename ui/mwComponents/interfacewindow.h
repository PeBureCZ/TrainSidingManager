#ifndef INTERFACEWINDOW_H
#define INTERFACEWINDOW_H

#include <QObject>
#include "mwComponents/mwlogic.h"
#include "Actors/Constructors/railselector.h"



class InterfaceWindow : public mwlogic
{
    Q_OBJECT
public:
    InterfaceWindow(mwlogic *parent = nullptr);
protected slots:
    void on_PlayBut_clicked() override;
    void on_SubBut_clicked() override;
    void on_AddBut_clicked() override;
    void playButSwitch(bool editMode) override;
    void selectMenuSwitch(bool selectMode) override;

    //MOUSE EVENTs
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void leftMouseRelease();
    void rightMouseRelease();
    void wheelEvent(QWheelEvent *event);


    //menu function buttons clicked
    void on_AddMenuBut_clicked() override;
    void on_EditMenuBut_clicked() override;

    //function buttons clicked
    void on_MultiFuncBut1_clicked() override;
    void on_MultiFuncBut2_clicked() override;
    void on_MultiFuncBut3_clicked() override;
    void on_MultiFuncBut4_clicked() override;
    void on_MultiFuncBut5_clicked() override;
    void on_MultiFuncBut6_clicked() override;
    void on_MultiFuncBut7_clicked() override;
    void on_MultiFuncBut8_clicked() override;
    void on_MultiFuncBut9_clicked() override;
    void on_MultiFuncBut10_clicked() override;
    void on_MultiFuncBut11_clicked() override;
    void on_MultiFuncBut12_clicked() override;
    void on_MultiFuncBut13_clicked() override;
    void on_MultiFuncBut14_clicked() override;
    void on_MultiFuncBut15_clicked() override;
    void on_MultiFuncBut16_clicked() override;
    void on_MultiFuncBut17_clicked() override;
    void on_MultiFuncBut18_clicked() override;
    void on_MultiFuncBut19_clicked() override;
    void on_MultiFuncBut20_clicked() override;
    void on_MultiFuncBut21_clicked() override;
    void on_MultiFuncBut22_clicked() override;
    void on_MultiFuncBut23_clicked() override;
    void on_MultiFuncBut24_clicked() override;
};

#endif // INTERFACEWINDOW_H
