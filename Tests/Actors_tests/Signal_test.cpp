#include "signal_test.h"

Signal_test::Signal_test(QObject *parent)
    : QObject{parent}
{

}

void Signal_test::getState_test()
{
    Signal testedSignal;
    QVERIFY(SignalState::SIGNAL_STOP == testedSignal.getState());
    QVERIFY(SignalState::SIGNAL_CUSTOM8 == testedSignal.getAllowedSignalState().size()-1);
}
