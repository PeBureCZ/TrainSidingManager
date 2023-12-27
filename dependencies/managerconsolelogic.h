#ifndef MANAGERCONSOLELOGIC_H
#define MANAGERCONSOLELOGIC_H

#include <QObject>
#include <QLabel>
#include <QChar>

class ManagerConsoleLogic : public QObject
{
    Q_OBJECT

protected:
    QLabel* consoleTextObject;
    int consoleLines;
    QList<int> timeSpan;
    QList<QString> consoleText;
public:
    explicit ManagerConsoleLogic(QObject *parent = nullptr);
    addToConsole(QString text, int timeToHidden);
    setConsolePos(QPoint point, int sizeX, int sizeY);
    reduceTimeSpan(int reduction);
    actualizeConsoleText();
    ~ManagerConsoleLogic();

signals:

};

#endif // MANAGERCONSOLELOGIC_H
