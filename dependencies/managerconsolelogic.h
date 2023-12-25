#ifndef MANAGERCONSOLELOGIC_H
#define MANAGERCONSOLELOGIC_H

#include <QObject>
#include <QLabel>
#include <QChar>

class ManagerConsoleLogic : public QObject
{
    Q_OBJECT

protected:
    QLabel* consoleText;
    int consoleLines;
    int timeSpan;
public:
    explicit ManagerConsoleLogic(QObject *parent = nullptr);
    addToConsole(QString text);
    setConsolePos(QPoint point, int sizeX, int sizeY);
    reduceTimeSpan(int reduction);
    actualizeConsoleText();
    ~ManagerConsoleLogic();




signals:

};

#endif // MANAGERCONSOLELOGIC_H
