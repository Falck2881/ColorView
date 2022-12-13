#include "Image.h"
#include <QIODevice>
#include <QImage>
#include <QSet>
#include <QtGlobal>
#include <algorithm>
#include <QFile>

Fk::Image::Image(std::shared_ptr<Fk::Base::InitializeImg> initialize):
    init(initialize)
{
}

Fk::Image::Image(Fk::Image&& oldImg)
{
    this->init = oldImg.init;
}

Fk::Image::Image(Fk::Image& oldImg)
{
    this->init = oldImg.init;
}

QString Fk::Image::width() const
{
    QImage img = init->image();
    return QString::number(img.width());
}

QString Fk::Image::hight() const
{
    QImage img = init->image();
    return QString::number(img.height());
}

QString Fk::Image::numberColor() const
{
    QImage image = init->image();
    image.convertTo(QImage::Format_RGB32);
    QSet<QString> setColors;

    for(qint32 y = 0; y < image.height(); ++y)
        for(qint32 x = 0; x < image.width(); ++x)
            setColors << image.pixelColor(x,y).name();

    return QString::number(setColors.size());
}

QString Fk::Image::numberBitOnPix() const
{
    QImage image = init->image();
    image.convertTo(QImage::Format_RGB32);
    return QString::number(image.depth());
}

QString Fk::Image::sizeImgInByte() const
{
    QImage image = init->image();
    image.convertTo(QImage::Format_RGB32);
    return QString::number(image.sizeInBytes());
}

QString Fk::Image::formatFile() const
{
    using namespace std;
    QString currNameFile = init->nameFile();
    QString searchFormFile("bmp");
    const QChar* formFile = std::search(begin(currNameFile),end(currNameFile),
                                        default_searcher(begin(searchFormFile),
                                                         end(searchFormFile)));
    return QString(formFile);
}

QString Fk::Image::nameFile() const
{
    return init->nameFile();
}
