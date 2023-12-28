#include "spritecolection.h"

SpriteColection::SpriteColection()
{
    relativeDirectory = QApplication::applicationDirPath();
    filePath = {""};
}

QPixmap SpriteColection::empty()
{
    QPixmap pixmap;
    return pixmap;
}

QPixmap SpriteColection::loco()
{
    QPixmap pixmap(relativeDirectory + "/images/loco.png");
    return pixmap;
}

QPixmap SpriteColection::cd730()
{
    QPixmap pixmap(relativeDirectory + "/images/CD730.png");
    return pixmap;
}

QPixmap SpriteColection::redSignal()
{
    QPixmap pixmap(relativeDirectory + "/images/signal_red.png");
    return pixmap;
}

QPixmap SpriteColection::greenSignal()
{
    QPixmap pixmap(relativeDirectory + "/images/signal_green.png");
    return pixmap;
}

QPixmap SpriteColection::yellowSignal()
{
    QPixmap pixmap(relativeDirectory + "/images/signal_yellow.png");
    return pixmap;
}

QPixmap SpriteColection::whiteSignal()
{
    QPixmap pixmap(relativeDirectory + "/images/signal_white.png");
    return pixmap;
}
