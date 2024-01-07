#include "Image.h"
#include <QSet>
#include <QFileInfo>
#include <QPixmap>
#include <thread>
#include <QPainter>
#include <QByteArray>
#include <QImageReader>
#include <QGuiApplication>
#include <QScreen>
#include <QGraphicsSceneMouseEvent>

Fk::Image::Image():absPathToFile("")
{

}

Fk::Image::Image(const Fk::Image& copyObj)
{
    this->image = copyObj.image;
    this->absPathToFile = copyObj.absPathToFile;
    this->setColors = copyObj.setColors;
}

Fk::Image::Image(Fk::Image&& copyObj)
{
    this->image = copyObj.image;
    this->absPathToFile = copyObj.absPathToFile;
    this->setColors = copyObj.setColors;
}

Fk::Image& Fk::Image::operator=(Fk::Image &&copyObj)
{
    if(this == &copyObj)
        return *this;

    this->image = copyObj.image;
    this->absPathToFile = copyObj.absPathToFile;
    this->setColors = copyObj.setColors;

    return *this;
}

Fk::Image& Fk::Image::operator=(const Fk::Image &copyObj)
{
    if(this == &copyObj)
        return *this;

    this->image = copyObj.image;
    this->absPathToFile = copyObj.absPathToFile;
    this->setColors = copyObj.setColors;

    return *this;
}

Fk::Image::Image(const QString pathFile):
    image(pathFile,nullptr),
    absPathToFile(pathFile)
{
    if(!image.isNull()){
        setAllNameColorsInSet();
        type = TypeImage::SimpleImage;
    }
    else{
        fillImageWithWhiteColor();
        type = TypeImage::DrawImage;
    }
}

void Fk::Image::setAllNameColorsInSet()
{
    if(!setColors.isEmpty())
        setColors.clear();

    for(qint32 y = 0; y < image.height(); ++y)
        for(qint32 x = 0; x < image.width(); ++x)
            setColors << image.pixelColor(x,y).name();
}

void Fk::Image::fillImageWithWhiteColor()
{
    auto screen = QGuiApplication::primaryScreen()->availableGeometry().size();
    quint32 width = screen.width() * 1.2;
    quint32 height = screen.height() * 1.2;

    image = QImage(width, height, QImage::Format_RGB32);

    for (int x = 0; x < image.width(); ++x) {
        for (int y = 0; y < image.height(); ++y) {
            setPixelColor(x, y, QColor(Qt::white));
        }
    }
}

Fk::TypeImage Fk::Image::getType() const
{
    return type;
}

bool Fk::Image::isNull() const
{
    return image.isNull();
}

bool Fk::Image::is32BitsOnPixel() const
{
    return numberBitOnPix() == "32";
}

bool Fk::Image::is24BitsOnPixel() const
{
    return numberBitOnPix() == "24";
}

bool Fk::Image::is16BitsOnPixel() const
{
    return numberBitOnPix() == "16";
}

bool Fk::Image::is8BitsOnPixel() const
{
    return numberBitOnPix() == "8";
}

void Fk::Image::setDepthColor(QImage::Format depthColor)
{
    image = image.convertToFormat(depthColor,Qt::ColorOnly);

    setAllNameColorsInSet();
}

bool Fk::Image::save(const QString newAbsPathToFile, const QString newFormat)
{
    if(newAbsPathToFile.contains(newFormat)){
        return image.save(newAbsPathToFile,nullptr,90);
    }
    else{
        QByteArray arr{newFormat.toLatin1()};
        return image.save(newAbsPathToFile + "." + newFormat, arr.data(), 90);
    }

}

QPixmap Fk::Image::pixmap() const
{
    return QPixmap::fromImage(image);
}

QImage Fk::Image::context() const
{
    return image;
}

void Fk::Image::updateContext(const QImage& newImage)
{
    image = newImage;
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

QString Fk::Image::toFormat() const
{
    QByteArray byteFormat{QImageReader::imageFormat(absPathToFile)};
    return QString(byteFormat);
}

QString Fk::Image::nameFile() const
{
    QFileInfo fileInfo(absPathToFile);
    return fileInfo.fileName();
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
