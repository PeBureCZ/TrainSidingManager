#ifndef TRAINNAVIGATION_TEST_H
#define TRAINNAVIGATION_TEST_H

#include <QObject>
#include "dependencies/trainnavigation.h"

class TrainNavigation_test : public QObject
{
    Q_OBJECT
private slots:
    void checkNewDirection_test();
public:
    explicit TrainNavigation_test(QObject *parent = nullptr);


signals:

};

#endif // TRAINNAVIGATION_TEST_H
