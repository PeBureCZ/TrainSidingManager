#ifndef SIGNAL_TEST_H
#define SIGNAL_TEST_H

#include <QObject>
#include "Actors/signal.h"
#include "QtTest"

class Signal_test : public QObject
{
    Q_OBJECT
public:
    explicit Signal_test(QObject *parent = nullptr);

private slots:
    void getState_test();


signals:

};

#endif // SIGNAL_TEST_H
