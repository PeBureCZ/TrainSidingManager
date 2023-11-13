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
