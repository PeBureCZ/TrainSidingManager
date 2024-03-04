#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QLayout>
#include <QWidget>

#include "dependencies/worldmap.h"
#include "dependencies/managerconsole.h"
#include "dependencies/Enums/MainWindowEnum.h"
#include "Actors/Constructors/railselector.h"
#include "dependencies/spritecolection.h"
#include <QApplication>

/*
menuSelected:
0-99 = menu option
100-199 = edit add mode
200-299 = edit select/edit mode
300-399 = play add mode
400-499 = play select/edit mode
*/

enum iconEnums
{
    EMPTY_ICON,
    CHANGEDIR_ICON,
    LOAD_ICON,
    MOVE_ICON,
    PATH_ICON,
    PORTAL_ICON,
    RAIL_ICON,
    SIGNAL_ICON,
    TRAIN_ICON,
    UNCOUPLE_ICON,
    UNLOAD_ICON,
    VIA_ICON,
    EXIT_ICON,
    BIN_ICON,
    MOTOR_ICON,
};

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

private:
    void resizeEvent(QResizeEvent *event) override;
    QVector<QString> relativeIconPaths;

public:
    MainWindow(QWidget *parent = nullptr);   
    ~MainWindow();
    void wheelEvent(QWheelEvent *event);
    void initializeInterface();
    virtual void playButSwitch(bool editMode);
    virtual void selectMenuSwitch(bool selectMode);

    //MENU TYPES
    void InterfaceSet(int menuSelected);
    void setBasicMenuInterface();
    void setEditSelectInterface();
    void setEditAddInterface();
    void setPlayAddInterface();
    void setTrainMenu();
    void setPlaySelectInterface();

    QVBoxLayout *consoleLayout;
    ManagerConsole* managerConsole;
    QHBoxLayout *mapZoomLayout;
    QWidget *ZoomWidget;

private slots:

    virtual void on_PlayBut_clicked();
    virtual void on_TestButton1_clicked();
    virtual void on_ZoomSubBut_clicked();
    virtual void on_ZoomAddBut_clicked();

    virtual void on_MultiFuncBut1_clicked();
    virtual void on_MultiFuncBut2_clicked();
    virtual void on_MultiFuncBut3_clicked();
    virtual void on_MultiFuncBut4_clicked();
    virtual void on_MultiFuncBut5_clicked();
    virtual void on_MultiFuncBut6_clicked();
    virtual void on_MultiFuncBut7_clicked();
    virtual void on_MultiFuncBut8_clicked();
    virtual void on_MultiFuncBut9_clicked();
    virtual void on_MultiFuncBut10_clicked();
    virtual void on_MultiFuncBut11_clicked();
    virtual void on_MultiFuncBut12_clicked();
    virtual void on_MultiFuncBut13_clicked();
    virtual void on_MultiFuncBut14_clicked();
    virtual void on_MultiFuncBut15_clicked();
    virtual void on_MultiFuncBut16_clicked();
    virtual void on_MultiFuncBut17_clicked();
    virtual void on_MultiFuncBut18_clicked();
    virtual void on_MultiFuncBut19_clicked();
    virtual void on_MultiFuncBut20_clicked();
    virtual void on_MultiFuncBut21_clicked();
    virtual void on_MultiFuncBut22_clicked();
    virtual void on_MultiFuncBut23_clicked();
    virtual void on_MultiFuncBut24_clicked();

    virtual void on_AddMenuBut_clicked();
    virtual void on_EditMenuBut_clicked();

protected:
    Ui::MainWindow *ui;
    WorldMap* world;
};
#endif // MAINWINDOW_H
