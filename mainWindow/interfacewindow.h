#ifndef INTERFACEWINDOW_H
#define INTERFACEWINDOW_H

#include <QObject>
#include "mainWindow/mwlogic.h"



class InterfaceWindow : public mwlogic
{
    Q_OBJECT
public:
    InterfaceWindow(mwlogic *parent = nullptr);
private slots:
    //void on_TestButton1_clicked();
    void on_PlayBut_clicked() override;
    void on_SubBut_clicked() override;
    void on_AddBut_clicked() override;
    void mousePressEvent(QMouseEvent *event);
    void wheelEvent(QWheelEvent *event);
    void playButSwitch(bool editMode) override;
    void selectMenuSwitch(bool selectMode) override;

    //menu function buttons clicked
    void on_AddMenuBut_clicked() override;
    void on_EditMenuBut_clicked() override;

    //function buttons clicked
    void on_MultiFuncBut1_clicked() override;
    void on_MultiFuncBut2_clicked() override;
    void on_MultiFuncBut24_clicked() override;

};

#endif // INTERFACEWINDOW_H
