#include "managerconsolelogic.h"

ManagerConsoleLogic::ManagerConsoleLogic(QObject *parent)
    : QObject{parent}
{
    consoleTextObject = new QLabel("", dynamic_cast<QWidget*>(parent));
    consoleTextObject->setAlignment(Qt::AlignBottom);
    consoleLines = 0;
    timeSpan = {};
    consoleText = {};
}

void ManagerConsoleLogic::addToConsole(QString text, int timeToHidden)
{
    //visual size = max 14 rows
    timeSpan.push_back(timeToHidden);
    consoleText.push_back(text);
    consoleLines++;
    if (consoleLines > 13)
    {
        consoleText.remove(0,1);
        timeSpan.remove(0,1);
        consoleLines--;
    }
    consoleTextObject->clear();
    QString newText = "";
    actualizeConsoleText();
}

void ManagerConsoleLogic::setConsolePos(QPoint point, int sizeX, int sizeY)
{
    consoleTextObject->setGeometry(point.x(), point.y(), sizeX, sizeY);
}

void ManagerConsoleLogic::reduceTimeSpan(int reduction)
{
    bool actualize = false;
    if (consoleText.size() > 0)
    {

        for (int i = timeSpan.size() -1; i >= 0 ; i--)
        {
            timeSpan[i]--;
            if (timeSpan[i] <= 0)
            {
                actualize = true;
                timeSpan.remove(i,1);
                consoleText.remove(i,1);
                consoleLines--;
            }
        }
    }
    if (actualize) actualizeConsoleText();
}

void ManagerConsoleLogic::actualizeConsoleText()
{
    QString textInConsole = "";
    consoleTextObject->clear();
    for (int i = 0; i < timeSpan.size(); i++)
    {
        textInConsole += "<br>" + consoleText[i];
    }
    consoleTextObject->setText(textInConsole);
}


ManagerConsoleLogic::~ManagerConsoleLogic(){}

