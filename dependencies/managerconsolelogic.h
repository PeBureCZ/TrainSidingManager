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
    void addToConsole(QString text, int timeToHidden);
    void setConsolePos(QPoint point, int sizeX, int sizeY);
    void reduceTimeSpan(int reduction);
    void actualizeConsoleText();
    ~ManagerConsoleLogic();

signals:

};

#endif // MANAGERCONSOLELOGIC_H
