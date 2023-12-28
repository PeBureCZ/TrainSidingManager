#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "dependencies/worldmap.h"
#include <QLabel>
#include <QLayout>
#include "dependencies/managerconsole.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
private:
    void resizeEvent(QResizeEvent *event) override;

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void wheelEvent(QWheelEvent *event);
    void initializeInterface();
    virtual void playButSwitch(bool editMode);
    void InterfaceSet(int menuSelected);
    QVBoxLayout *consoleLayout;
    ManagerConsole* managerConsole;

private slots:

    virtual void on_PlayBut_clicked();
    virtual void on_TestButton1_clicked();
    virtual void on_SubBut_clicked();
    virtual void on_AddBut_clicked();

    virtual void on_MultiFuncBut1_clicked();
    virtual void on_MultiFuncBut2_clicked();
    virtual void on_MultiFuncBut24_clicked();


protected:
    Ui::MainWindow *ui;
    WorldMap* world;

};
#endif // MAINWINDOW_H
