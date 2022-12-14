#include "Image.h"
#include "FilterImage.h"
#include <QSet>
#include <QFileInfo>
#include <QPixmap>
#include <thread>
#include <QPainter>

Fk::Image::Image(const Fk::Image& copyObj)
{
    this->image = copyObj.image;
    this->charFormat = copyObj.charFormat;
    this->absPathToFile = copyObj.absPathToFile;
    this->strFormat = copyObj.strFormat;
}

Fk::Image::Image(Fk::Image&& copyObj)
{
    this->image = copyObj.image;
    this->charFormat = copyObj.charFormat;
    copyObj.charFormat = nullptr;
    this->absPathToFile = copyObj.absPathToFile;
    this->strFormat = copyObj.strFormat;
}

Fk::Image& Fk::Image::operator=(Fk::Image &&copyObj)
{
    if(this == &copyObj)
        return *this;

    this->image = copyObj.image;
    this->charFormat = copyObj.charFormat;
    copyObj.charFormat = nullptr;
    this->absPathToFile = copyObj.absPathToFile;
    this->strFormat = copyObj.strFormat;

    return *this;
}

Fk::Image& Fk::Image::operator=(const Fk::Image &copyObj)
{
    if(this == &copyObj)
        return *this;

    this->image = copyObj.image;
    this->charFormat = copyObj.charFormat;
    this->absPathToFile = copyObj.absPathToFile;
    this->strFormat = copyObj.strFormat;

    return *this;
}

Fk::Image::Image(const QString pathFile, const char* format):
    image(pathFile,format),
    charFormat(const_cast<char*>(format)),
    absPathToFile(pathFile),
    strFormat(format)
{
    image = image.scaled(QSize(1024,768),Qt::KeepAspectRatio);
}

bool Fk::Image::save(const QString newAbsPathToFile,const char* newFormat) const
{
    return image.save(newAbsPathToFile,newFormat,90);
}

QPixmap Fk::Image::pixmap()
{
    return QPixmap::fromImage(image);
}

QImage& Fk::Image::qImage()
{
    return image;
}

qint32 Fk::Image::width() const
{
    return image.width();
}

qint32 Fk::Image::height() const
{
    return image.height();
}

QString Fk::Image::numberColor() const
{
    QSet<QString> setColors;

    for(qint32 y = 0; y < image.height(); ++y)
        for(qint32 x = 0; x < image.width(); ++x)
            setColors << image.pixelColor(x,y).name();

    return QString::number(setColors.size());
}

QString Fk::Image::sizeImgInByte() const
{
    return QString::number(image.sizeInBytes());
}

QString Fk::Image::numberBitOnPix() const
{
    return QString::number(image.depth());
}

char* Fk::Image::toCharFormat() const
{
    return charFormat;
}

QString Fk::Image::toStrFormat() const
{
    return strFormat;
}

QString Fk::Image::nameFile() const
{
    QFileInfo fileInfo(absPathToFile);
    QString fileName;
    if(fileInfo.exists())
        fileName = fileInfo.fileName();

    return fileName;
}


QString Fk::Image::absolutlePathToFile() const
{
    QFileInfo fileInfo(absPathToFile);
    QString absolutlePathToFile;
    if(fileInfo.exists())
        absolutlePathToFile = fileInfo.absoluteFilePath();

    return absolutlePathToFile;
}

void Fk::Image::scaled(const quint32 width, const quint32 hight)
{
    image = image.scaled(width,hight,Qt::KeepAspectRatio);
}

void Fk::Image::setFilter(std::shared_ptr<FilterImage> filter)
{
    filter->applyFilter(this);

}

void Fk::Image::setFraming(const QString nameFileFrame)
{
    quint32 width = image.width();
    quint32 height = image.height();

    QPainter painter(&image);
    QPixmap frameImg(nameFileFrame);
    frameImg = frameImg.scaled(width,height);
    painter.drawPixmap(0,0,frameImg);
}
