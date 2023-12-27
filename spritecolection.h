#ifndef SPRITECOLECTION_H
#define SPRITECOLECTION_H

#include <QString>
#include <QApplication>
#include <QVector>
#include <QPixmap>
#include <QGraphicsPixmapItem>

struct SpriteColection
{
    QString relativeDirectory;
    QVector<QString> filePath;
    SpriteColection();
    QPixmap empty();
    QPixmap loco();
    QPixmap cd730();
    QPixmap redSignal();
    QPixmap greenSignal();
    QPixmap yellowSignal();
    QPixmap whiteSignal();
};

#endif // SPRITECOLECTION_H
