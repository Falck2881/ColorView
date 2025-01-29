#ifndef FKIMAGE_H
#define FKIMAGE_H

#include <QtGlobal>
#include <QImage>
#include <QSet>
#include <memory>
#include <QPointF>

class QPixmap;
class QColor;

namespace Fk {

    enum class TypeImage{DrawImage, SimpleImage};

    // Максимальная ширина изображения
    enum MaxWidthImage{W1600 = 1600, W1280 = 1280, W1024 = 1024, W800 = 800, W640 = 640};

    // Максимальная высота изображения
    enum MaxHeightImage{H1200 = 1200, H1024 = 1024, H768 = 768, H600 = 600, H480 = 480};

    class Image
    {
        public:
            Image();
            Image(const Fk::Image& copyObj);
            Image(Fk::Image&& copyObj);
            Fk::Image& operator=(Fk::Image&& oldImage);
            Fk::Image& operator=(const Fk::Image& oldImage);
            Image(const QString nameFile);
            bool isNull() const;
            bool is32BitsOnPixel() const;
            bool is24BitsOnPixel() const;
            bool is16BitsOnPixel() const;
            bool is8BitsOnPixel() const;
            void setDepthColor(QImage::Format depthColor);
            bool save(const QString newAbsPathToFile, const QString newFormats);
            QPixmap pixmap() const;
            QImage context() const;
            void updateContext(const QImage& newImage);
            QColor pixel(qint32 x, qint32 y) const;
            void setPixelColor(qint32 x, qint32 y, QColor newColor);
            const uchar* scanLine(const qsizetype y) const;
            qint32 width() const;
            qint32 height() const;
            QString numberColor() const;
            QString sizeImgInByte() const;
            QString numberBitOnPix() const;
            QString toFormat() const;
            QString nameFile() const;
            QString absolutlePathToFile() const;
            void scaled(const quint32 width, const quint32 hight);
            void setFraming(const QString nameFileFrame);
            TypeImage getType() const;
       private:
            bool isBigSize();
            int defineWidth();
            int defineHeight();
            void setAllNameColorsInSet();
            void fillImageWithWhiteColor();
       private:
            QImage image;
            QString absPathToFile;
            QSet<QString> setColors;
            QPointF moveDraw;
            TypeImage type;
    };
}
#endif // FKIMAGE_H
