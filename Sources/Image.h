#ifndef IMAGE_H
#define IMAGE_H

#include <QtGlobal>
#include <QImage>
#include <QSet>
#include <memory>
#include "Billboard.h"

class QPixmap;
class QColor;

namespace Fk {

    class Image: public Billboard
    {
        public:
            Image();
            Image(const Fk::Image& copyObj);
            Image(Fk::Image&& copyObj);
            Fk::Image& operator=(Fk::Image&& oldImage);
            Fk::Image& operator=(const Fk::Image& oldImage);
            Image(const QString nameFile, const QString format);
            bool isNull() const;
            bool isHighQuality() const;
            bool is16BitsOnPixel() const;
            bool is8BitsOnPixel() const;
            void setDepthColor(QImage::Format depthColor);
            bool save(const QString newAbsPathToFile, const QString newFormats) override;
            QPixmap pixmap() const;
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
       private:
            void setAllNameColorsInSet();
       private:
            QImage image;
            QString absPathToFile;
            QString format;
            QSet<QString> setColors;
    };
}
#endif // IMAGE_H
