#ifndef CONSOLEENUMS_H
#define CONSOLEENUMS_H

#include <QVector>
#include <QString>

enum colors
{
    DEFAULT_COLOR,
    RED_BOLD_COLOR,
    BLUE_BOLD_COLOR,
    GREEN_BOLD_COLOR,
    BLACK_BOLD_COLOR,
    WHITE_BOLD_COLOR,
    YELLOW_BOLD_COLOR,
    RED_COLOR,
    BLUE_COLOR,
    GREEN_COLOR,
    BLACK_COLOR,
    WHITE_COLOR,
    YELLOW_COLOR
};

enum durationOfText //IN TICK TIME (30ms)
{
    INSTANT_DURATION = 10,
    SHORT_DURATION = 50,
    MIDDLE_DURATION = 150,
    LONG_DURATION = 400,
    VERY_LONG_DURATION = 800,

};

struct ConsoleTextsStruct
{
public:
    const QVector<QString>messageText =
    {
        "To create a portal, click (LMB) on any rail.The portal allows you to create trains; the length of trains (number of attached wagons)",
        " depends on the length of the rail that is transformed into a portal",

        "For marking the track, click the left mouse button on the light blue highlighted track",

        "To place a signal, move the mouse cursor closer to the breakpoints of one of the tracks. The track with the placed signal will be marked with a changed color",
        "(To confirm the placement of a signal on the track, use the left mouse button (LMB))",

        "To place a track, click the left mouse button (LMB) on the surface. To delete, use the right mouse button (RMB)",
        "(To connect to another track, use the left mouse button (LMB) near the end of another track)",
    };
};

enum consoleTexts
{
    PORTAL_CONSOLE_TEXT1 = 0,
    PORTAL_CONSOLE_TEXT2,
    RAIL_SELECTOR_CONSOLE_TEXT,
    SIGNAL_CONSOLE_TEXT1,
    SIGNAL_CONSOLE_TEXT2,
    RAIL_CONSOLE_TEXT1,
    RAIL_CONSOLE_TEXT2,
};

#endif // CONSOLEENUMS_H
