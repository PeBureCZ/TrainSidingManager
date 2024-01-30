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
    case 1: //red-bold
        colorizedText += "<font style=\"font-weight: bold; color: red;\">" + text + "</font>";
        break;
    case 2: //blue-bold
        colorizedText += "<font style=\"font-weight: bold; color: blue;\">" + text + "</font>";
        break;
    case 3: //green-bold
        colorizedText += "<font style=\"font-weight: bold; color: green;\">" + text + "</font>";
        break;
    case 4: //black-bold
        colorizedText += "<font style=\"font-weight: bold; color: black;\">" + text + "</font>";
        break;
    case 5: //white-bold
        colorizedText += "<font style=\"font-weight: bold; color: white;\">" + text + "</font>";
        break;
    case 6: //yellow-bold
        colorizedText += "<font style=\"font-weight: bold; color: yellow;\">" + text + "</font>";
        break;
    case 7: //red
        colorizedText += "<font color=\"red\">" + text + "</font>";
        break;
    case 8: //blue
        colorizedText += "<font color=\"blue\">" + text + "</font>";
        break;
    case 9: //green
        colorizedText += "<font color=\"green\">" + text + "</font>";
        break;
    case 10: //black
        colorizedText += "<font color=\"black\">" + text + "</font>";
        break;
    case 11: //white
        colorizedText += "<font color=\"white\">" + text + "</font>";
        break;
    case 12: //yellow
        colorizedText += "<font color=\"yellow\">" + text + "</font>";
        break;
    default:
        colorizedText += "<font color=\"gray\">" + text + "</font>";
        //

    }
    addToConsole(colorizedText, timeToHidden);
}

ManagerConsole::~ManagerConsole(){}
