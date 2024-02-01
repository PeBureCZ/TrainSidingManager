#ifndef ACTOR_TEST_H
#define ACTOR_TEST_H

#include <QTest>
#include "Actors/actor.h"
#include "Actors_tests/rail_test.h"

class Actor_test : public QObject
{
    Q_OBJECT
public:
    explicit Actor_test(QObject *parent = nullptr);

private slots:
    void initTestCase(); //not used
    void cleanupTestCase(); //not used
    void getName_test();
    void location_test();

public slots:


signals:

};
#endif // ACTOR_TEST_H
