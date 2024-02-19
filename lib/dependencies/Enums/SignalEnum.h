#ifndef SIGNALENUM_H
#define SIGNALENUM_H

enum SignalState
{
    //BASIC SIGNALIZATIONs
    SIGNAL_STOP = 0,
    SIGNAL_PROCEED,
    SIGNAL_CAUTION,
    SIGNAL_DOUBLE_CAUTION,
    SIGNAL_SHUNT,
    SIGNAL_FREE_CAUTION,
    SIGNAL_SLOW,
    SIGNAL_DANGER,

    //CUSTOM-ADDITIONAL SIGNALIZATIONs
    SIGNAL_CUSTOM1,
    SIGNAL_CUSTOM2,
    SIGNAL_CUSTOM3,
    SIGNAL_CUSTOM4,
    SIGNAL_CUSTOM5,
    SIGNAL_CUSTOM6,
    SIGNAL_CUSTOM7,
    SIGNAL_CUSTOM8 //last allowed signal in constructor
};





#endif // SIGNALENUM_H