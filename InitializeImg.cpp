#include "InitializeImg.h"

Fk::Base::InitializeImg::InitializeImg(const QString nameFileImg):
    currNameFileImg(nameFileImg),
    pixmap(nameFileImg),
    currImage(pixmap.toImage())
{

}

QImage Fk::Base::InitializeImg::image() const
{
    return currImage;
};

QString Fk::Base::InitializeImg::nameFile() const
{
    return currNameFileImg;
}

void Fk::Base::InitializeImg::saveNameFileImage(const QString nameFile)
{
    currNameFileImg = nameFile;
}

void Fk::Base::InitializeImg::loadImageFile()
{
    if(pixmap.load(currNameFileImg))
        currImage = pixmap.toImage();
}
