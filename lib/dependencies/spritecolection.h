#ifndef SPRITECOLECTION_H
#define SPRITECOLECTION_H

#include <QString>
#include <QApplication>
#include <QVector>
#include <QPixmap>
#include <array>
#include <QGraphicsPixmapItem>

enum spriteEnums
{
    //HAVE TO ADD TO "SpriteColection" STRUCT TOO!!!
    EMPTY_SPRITE = 0,

    LOCO_SPRITE,
    CD730_SPRITE,
    CD753_SPRITE,

    EAS_SPRITE,
    ZAES_SPRITE,

    RED_SIGNAL_SPRITE,
    GREEN_SIGNAL_SPRITE,
    YELLOW_SIGNAL_SPRITE,
    WHITE_SIGNAL_SPRITE,
    FULL_SIGNAL_SPRITE,
    NO_SIGNAL_SPRITE,

    RAIL_SPRITE,

    PORTAL_SPRITE,
};

struct SpriteColection
{
    const QVector<QString>relativePaths =
    {
        //HAVE TO ADD TO "spriteEnums" TOO!!!

        "",
        "/images/loco.png",
        "/images/CD730.png",
        "/images/CD753.png",

        "/images/Eas.png",
        "/images/Zaes.png",

        "/images/signal_red.png",
        "/images/signal_green.png",
        "/images/signal_yellow.png",
        "/images/signal_white.png",
        "/images/signal_full.png",
        "/images/signal_full_noPlace.png",

        "/images/rail.png",

        "/images/portal.png",
    };

    QString relativeDirectory;
    QVector<QString> filePath;
    SpriteColection();
    QPixmap getSprite(int indexOfSprite);

public slots:
};

#endif // SPRITECOLECTION_H
