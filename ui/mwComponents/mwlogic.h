#ifndef MWLOGIC_H
#define MWLOGIC_H

#include "../ui/mainWindow/mainwindow.h"
#include <QObject>
#include <QMouseEvent>
#include <QWheelEvent>
#include <QGraphicsView>
#include <QHBoxLayout>


//ENUM
#include "dependencies/Enums/BlockChannels.h"

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
    void selectMenuSwitch(bool selectMode) override;
    void addConstructor(int constructorType);
    void constructRail(QPoint point);
    void constructSignal();
    void constructPortal();
    void spawnPortalTrain(QPoint point);
    void trainSelect();
    void clickInTrainMenu();

};

#endif // MWLOGIC_H
