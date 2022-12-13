#ifndef IMAGE_H
#define IMAGE_H

#include <QPixmap>
#include <QString>
#include "InitializeImg.h"

namespace Fk {

    class Image
    {
        public:
            explicit Image(std::shared_ptr<Fk::Base::InitializeImg> initialize);
            Image(Image&& oldObj);
            Image(Image& oldObj);
            QString width() const;
            QString hight() const;
            QString numberColor() const;
            QString sizeImgInByte() const;
            QString numberBitOnPix() const;
            QString formatFile() const;
            QString nameFile() const;
        private:
            void saveBalckAndWhiteVersionImage();
            QImage getBlackWhiteImg();
        private:
            std::shared_ptr<Fk::Base::InitializeImg> init;
    };
}
#endif // IMAGE_H
