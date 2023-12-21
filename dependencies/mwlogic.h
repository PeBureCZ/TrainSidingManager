#ifndef MWLOGIC_H
#define MWLOGIC_H

#include <mainwindow.h>
#include <QObject>
#include <QMouseEvent>
#include <QWheelEvent>
#include <QGraphicsView>
#include <QHBoxLayout>
#include "Actors/actor.h"

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
    void mouseEvent(QMouseEvent* event);

};

#endif // MWLOGIC_H
