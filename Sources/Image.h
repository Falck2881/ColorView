#ifndef IMAGE_H
#define IMAGE_H

#include <QtGlobal>
#include <QImage>
#include <QString>
#include <mutex>
#include <memory>

class QPixmap;
class QColor;
class FilterImage;

namespace Fk {

    class Image
    {
        public:
            std::mutex mutex;
            Image() = default;
            Image(const Fk::Image& copyObj);
            Image(Fk::Image&& copyObj);
            Fk::Image& operator=(Fk::Image&& oldImage);
            Fk::Image& operator=(const Fk::Image& oldImage);
            Image(const QString nameFile, const char* format = nullptr);
            bool save(const QString newAbsPathToFile,const char* newFormat) const;
            QPixmap pixmap();
            QImage& qImage();
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
            void setFilter(std::shared_ptr<FilterImage> filter);
            void setFraming(const QString nameFileFrame);
            QImage image;
            char* charFormat;
            QString absPathToFile;
            QString strFormat;
    };
}
#endif // IMAGE_H
