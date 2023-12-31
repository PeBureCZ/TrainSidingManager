#ifndef MWLOGIC_H
#define MWLOGIC_H

#include <mainWindow/mainwindow.h>
#include <QObject>
#include <QMouseEvent>
#include <QWheelEvent>
#include <QGraphicsView>
#include <QHBoxLayout>
#include "Actors/actor.h"

/*
    menuSelected:
    0-99 = menu option
    100-199 = edit mode functionss
    200-299 = play mode functions
    */

class mwlogic : public MainWindow
{
    Q_OBJECT

signals:

private slots:

protected:
    int menuSelected;
    qint64 elapsedTime;
    bool playModeActualized;

public:
    mwlogic(MainWindow *parent = nullptr);
    ~mwlogic();
    void actualizeMap();
    void actualizeDeltaTime(qint64 deltaTime);
    void playButSwitch(bool editMode) override;
    void addConstructor(int constructorType, QPoint point);
    void constructRail(QPoint point);
    void constructSignal();
};

#endif // MWLOGIC_H
