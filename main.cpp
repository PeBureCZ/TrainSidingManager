#include "mainwindow.h"
#include <QApplication>
#include <Qtimer>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWindow w;

    QTimer timer;
    QObject::connect(&timer, &QTimer::timeout, [&]()
    {
        w.actualizeMap();
        //w.testFce();
        //timer.stop();
    });
    timer.start(3000);

    w.show();
    return a.exec();
}
