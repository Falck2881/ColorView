#include "Image.h"
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
    this->setColors = copyObj.setColors;
}

Fk::Image::Image(Fk::Image&& copyObj)
{
    this->image = copyObj.image;
    this->charFormat = copyObj.charFormat;
    copyObj.charFormat = nullptr;
    this->absPathToFile = copyObj.absPathToFile;
    this->strFormat = copyObj.strFormat;
    this->setColors = copyObj.setColors;
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
    this->setColors = copyObj.setColors;

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
    this->setColors = copyObj.setColors;

    return *this;
}

Fk::Image::Image(const QString pathFile, const char* format):
    image(pathFile,format),
    charFormat(const_cast<char*>(format)),
    absPathToFile(pathFile),
    strFormat(format)
{
    image = image.scaled(QSize(1024,768),Qt::KeepAspectRatio);
    setAllNameColorsInSet();
}

void Fk::Image::setAllNameColorsInSet()
{
    if(!setColors.isEmpty())
        setColors.clear();

    for(qint32 y = 0; y < image.height(); ++y)
        for(qint32 x = 0; x < image.width(); ++x)
            setColors << image.pixelColor(x,y).name();
}

bool Fk::Image::isNull() const
{
    return image.isNull();
}

void Fk::Image::setDepthColor(QImage::Format depthColor)
{
    image = image.convertToFormat(depthColor,Qt::ColorOnly);

    setAllNameColorsInSet();
}

bool Fk::Image::save(const QString newAbsPathToFile,const char* newFormat) const
{
    if(!newAbsPathToFile.contains(newFormat))
        return image.save(newAbsPathToFile + "." + newFormat,newFormat,90);
    else
        return image.save(newAbsPathToFile,nullptr,90);
}

QPixmap Fk::Image::pixmap() const
{
    return QPixmap::fromImage(image);
}

QColor Fk::Image::pixel(qint32 x, qint32 y) const
{
    return image.pixelColor(x, y);
}

void Fk::Image::setPixelColor(qint32 x, qint32 y, QColor newColor)
{
    image.setPixelColor(x, y, newColor);
}

const uchar* Fk::Image::scanLine(const qsizetype y) const
{
    return image.scanLine(y);
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

void Fk::Image::setFraming(const QString nameFileFrame)
{
    quint32 width = image.width();
    quint32 height = image.height();

    QPainter painter(&image);
    QPixmap frameImg(nameFileFrame);
    frameImg = frameImg.scaled(width,height);
    painter.drawPixmap(0,0,frameImg);
}
