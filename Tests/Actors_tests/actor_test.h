#ifndef ACTOR_TEST_H
#define ACTOR_TEST_H

#include <QTest>
#include "Actors/actor.h"

class Actor_test : public QObject
{
    Q_OBJECT
public:
    explicit Actor_test(QObject *parent = nullptr);

private slots:
    void getName_test();
    void location_test();
public slots:
    void full_test();

signals:

};
#endif // ACTOR_TEST_H
