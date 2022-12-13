#ifndef INITIALIZEIMG_H
#define INITIALIZEIMG_H

#include <QPixmap>
#include <QImage>
#include <QString>
#include <memory>

namespace Fk::Base
{
    class InitializeImg
    {
        protected:
            QString currNameFileImg;
            QPixmap pixmap;
            QImage currImage;
        public:
            ~InitializeImg() = default;
            QImage image() const;
            QString nameFile() const;
        protected:
            InitializeImg(const QString nameFileImg);
            void loadImageFile();
            void saveNameFileImage(const QString nameFileImg);
    };
}
#endif // RENDER_H
