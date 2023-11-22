#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QDebug>

#include <QMainWindow>
#include <QMouseEvent>
#include <QWheelEvent>
#include <QGraphicsView>
#include <QHBoxLayout>
#include "worldmap.h"
#include "Actors/actor.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void actualizeMap();

private slots:
    void on_TestButton1_clicked();
    void on_testButton2_clicked();
    void on_SubBut_clicked();
    void on_AddBut_clicked();
    void on_AddRailBut_clicked();
    void on_MoveBut_clicked();
    void mousePressEvent(QMouseEvent *event);
    void wheelEvent(QWheelEvent *event);

private:
    Ui::MainWindow *ui;
    WorldMap* world;
    int menuSelected;
    void initializeMap();

};
#endif // MAINWINDOW_H
