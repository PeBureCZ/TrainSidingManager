#include "managerconsolelogic.h"

ManagerConsoleLogic::ManagerConsoleLogic(QObject *parent)
    : QObject{parent}
{
    consoleText = new QLabel("", dynamic_cast<QWidget*>(parent));
    consoleText->setAlignment(Qt::AlignBottom);
    consoleLines = 0;
    timeSpan = 0;
    consoleText->clear();
    //consoleText->raise();
}

ManagerConsoleLogic::addToConsole(QString text)
{
    //visual size = max 14 rows
    timeSpan = 80;
    QString newText = consoleText->text();
    newText += "<br>" + text;
    consoleText->setText(newText);
    consoleLines++;
}

ManagerConsoleLogic::setConsolePos(QPoint point, int sizeX, int sizeY)
{
    consoleText->setGeometry(point.x(), point.y(), sizeX, sizeY);
}

ManagerConsoleLogic::reduceTimeSpan(int reduction)
{ 
    if (timeSpan > 0)
    {
        timeSpan--;
        if (timeSpan == 0)
        {
            actualizeConsoleText();
        }
    }
}

ManagerConsoleLogic::actualizeConsoleText()
{
    if (consoleLines == 1)
    {
        consoleLines--;
        consoleText->clear();
    }
    else if (consoleLines > 0)
    {
        int letterIndex = 4; //start after <br> at index 4 (<br>.....QString chars)
        //delete one line (first)
        QString textInConsole = consoleText->text();
        consoleLines--;
        for (int i = 4; i < textInConsole.size(); i++)
        {
            if (textInConsole[i] == '<')
            {
                textInConsole.remove(0,i);
                timeSpan = 80;
                consoleText->setText(textInConsole);
                break;
            }
            else letterIndex++;
        }
    }
}

ManagerConsoleLogic::~ManagerConsoleLogic(){}

