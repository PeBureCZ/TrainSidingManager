#include "managerconsole.h"

ManagerConsole::ManagerConsole(QObject *parent)
    : ManagerConsoleLogic{parent}
{

}

void ManagerConsole::printToConsole(QString text, int color, int timeToHidden)
{ 
    QString colorizedText = "";
    switch(color)
    {
    case RED_BOLD_COLOR:
        colorizedText += "<font style=\"font-weight: bold; color: red;\">" + text + "</font>";
        break;
    case BLUE_BOLD_COLOR:
        colorizedText += "<font style=\"font-weight: bold; color: blue;\">" + text + "</font>";
        break;
    case GREEN_BOLD_COLOR:
        colorizedText += "<font style=\"font-weight: bold; color: green;\">" + text + "</font>";
        break;
    case BLACK_BOLD_COLOR:
        colorizedText += "<font style=\"font-weight: bold; color: black;\">" + text + "</font>";
        break;
    case WHITE_BOLD_COLOR:
        colorizedText += "<font style=\"font-weight: bold; color: white;\">" + text + "</font>";
        break;
    case YELLOW_BOLD_COLOR:
        colorizedText += "<font style=\"font-weight: bold; color: yellow;\">" + text + "</font>";
        break;
    case RED_COLOR:
        colorizedText += "<font color=\"red\">" + text + "</font>";
        break;
    case BLUE_COLOR:
        colorizedText += "<font color=\"blue\">" + text + "</font>";
        break;
    case GREEN_COLOR:
        colorizedText += "<font color=\"green\">" + text + "</font>";
        break;
    case BLACK_COLOR:
        colorizedText += "<font color=\"black\">" + text + "</font>";
        break;
    case WHITE_COLOR:
        colorizedText += "<font color=\"white\">" + text + "</font>";
        break;
    case YELLOW_COLOR:
        colorizedText += "<font color=\"yellow\">" + text + "</font>";
        break;
    default:
        colorizedText += "<font color=\"gray\">" + text + "</font>";
        //
    }
    addToConsole(colorizedText, timeToHidden);
}

ManagerConsole::~ManagerConsole(){}
