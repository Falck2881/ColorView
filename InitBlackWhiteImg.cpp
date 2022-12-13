#include "InitBlackWhiteImg.h"
#include <QFile>

Fk::Init::BlackWhite::BlackWhite(const QString nameFile):Fk::Base::InitializeImg(nameFile)
{
    initialize();
}

void Fk::Init::BlackWhite::initialize()
{
    QString nameNewFile("shipBlackWhite.bmp");
    QFile file(nameNewFile);

    if(!file.exists())
    {
        for(qint32 y = 0; y < currImage.height(); ++y)
        {
            for(qint32 x = 0; x < currImage.width(); ++x)
            {
                QColor color = currImage.pixel(x,y);
                quint32 averaged = (qRed(color.red()) + qGreen(color.green()) + qBlue(color.blue()))/3;
                currImage.setPixelColor(x,y,qRgb(averaged,averaged,averaged));
            }
        }

        currImage.save(nameNewFile,"bmp");
        saveNameFileImage(nameNewFile);
    }
    else{
        saveNameFileImage(nameNewFile);
        loadImageFile();
    }
}
