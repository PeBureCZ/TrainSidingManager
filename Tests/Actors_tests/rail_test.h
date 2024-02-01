#ifndef RAIL_TEST_H
#define RAIL_TEST_H

#include <QObject>
#include "Actors/rail.h"
#include <QTest>

class Rail_test : public QObject
{
    Q_OBJECT
public:
    explicit Rail_test(QObject *parent = nullptr);
    ~Rail_test();
private slots:
    void setConnectedRail_test();

    void connectRails_oneRail_test();
    void connectRails_threeRailsOnStart_test();
    void connectRails_fullRails_test();
    void connectRails_threeRailsOnEnd_test();

    void connectRails_connectA0ToP0();
    void connectRails_connectA0ToP3();

    void connectRails_connecC1ToP0();
    void connectRails_connectC1ToP3();

public slots:

signals:

};

#endif // RAIL_TEST_H
