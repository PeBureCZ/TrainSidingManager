#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "dependencies/worldmap.h"
#include <QLabel>
#include <QLayout>
#include "dependencies/managerconsole.h"
#include "dependencies/Enums/MainWindowEnum.h"
#include "Actors/Constructors/railselector.h"

/*
menuSelected:
0-99 = menu option
100-199 = edit add mode
200-299 = edit select/edit mode
300-399 = play add mode
400-499 = play select/edit mode
*/

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
private:
    void resizeEvent(QResizeEvent *event) override;
    void setBasicMenuInterface(int menu);
    void setEditSelectInterface(int menu);
    void setEditAddInterface(int menu);
    void setPlaySelectInterface(int menu);
    void setPlayAddInterface(int menu);
    void setDefaultInterface();

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void wheelEvent(QWheelEvent *event);
    void initializeInterface();
    virtual void playButSwitch(bool editMode);
    virtual void selectMenuSwitch(bool selectMode);
    void InterfaceSet(int menuSelected);

    QVBoxLayout *consoleLayout;
    ManagerConsole* managerConsole;
    QHBoxLayout *mapZoomLayout;
    QWidget *widgetWithLayout;

private slots:

    virtual void on_PlayBut_clicked();
    virtual void on_TestButton1_clicked();
    virtual void on_SubBut_clicked();
    virtual void on_AddBut_clicked();

    virtual void on_MultiFuncBut1_clicked();
    virtual void on_MultiFuncBut2_clicked();
    virtual void on_MultiFuncBut24_clicked();
    virtual void on_AddMenuBut_clicked();
    virtual void on_EditMenuBut_clicked();



protected:
    Ui::MainWindow *ui;
    WorldMap* world;

};
#endif // MAINWINDOW_H
