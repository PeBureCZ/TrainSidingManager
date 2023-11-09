#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMouseEvent>
#include <QWheelEvent>
#include <QGraphicsView>
#include <QHBoxLayout>
#include "worldmap.h"

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
    void testFce();

private slots:
    void on_TestButton_clicked();
    void mousePressEvent(QMouseEvent *event);
    void wheelEvent(QWheelEvent *event);
    void on_SubBut_clicked();
    void on_AddBut_clicked();
    void on_AddRailBut_clicked();

    void on_MoveBut_clicked();

private:
    Ui::MainWindow *ui;
    WorldMap* world;
    int menuSelected;
    void initializeMap();

};
#endif // MAINWINDOW_H
