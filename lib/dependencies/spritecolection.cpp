#include "spritecolection.h"

SpriteColection::SpriteColection()
{
    relativeDirectory = QApplication::applicationDirPath();
}

QPixmap SpriteColection::getSprite(int indexOfSprite)
{
    QPixmap pixmap;
    if (indexOfSprite == EMPTY_SPRITE) return pixmap;
    pixmap.load(relativeDirectory + relativePixmapPaths[indexOfSprite]);
    return pixmap;
}
