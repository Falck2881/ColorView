#ifndef IMAGE_H
#define IMAGE_H

#include <QtGlobal>
#include <QImage>
#include <QString>
#include <memory>

class QPixmap;
class QColor;

namespace Fk {

    class Image
    {
        public:
            Image() = default;
            Image(const Fk::Image& copyObj);
            Image(Fk::Image&& copyObj);
            Fk::Image& operator=(Fk::Image&& oldImage);
            Fk::Image& operator=(const Fk::Image& oldImage);
            Image(const QString nameFile, const char* format = nullptr);
            bool save(const QString newAbsPathToFile,const char* newFormat) const;
            QPixmap pixmap() const;
            QColor pixel(qint32 x, qint32 y) const;
            void setPixelColor(qint32 x, qint32 y, QColor newColor);
            const uchar* scanLine(const qsizetype y) const;
            qint32 width() const;
            qint32 height() const;
            QString numberColor() const;
            QString sizeImgInByte() const;
            QString numberBitOnPix() const;
            char* toCharFormat() const;
            QString toStrFormat() const;
            QString nameFile() const;
            QString absolutlePathToFile() const;
            void scaled(const quint32 width, const quint32 hight);
            void setFraming(const QString nameFileFrame);
            QImage image;
            char* charFormat;
            QString absPathToFile;
            QString strFormat;
    };
}
#endif // IMAGE_H
