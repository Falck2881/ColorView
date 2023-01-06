#include "ThreadProcessingImages.h"

ThreadProcessingImages::ThreadProcessingImages
(QVector<std::shared_ptr<ConversionColor>> methodsConversionColor):
    methodsConversionColor(methodsConversionColor)
{
    moveToThread(&thread);
}

void ThreadProcessingImages::start()
{
    thread.start();
}

void ThreadProcessingImages::applyProcessing(const Fk::Image& image)
{
    QVector<Fk::Image> processingImages;
    processingImages << image << image << image << image << image << image;

    auto iterImg{processingImages.begin()};
    auto iterMethods{methodsConversionColor.begin()};

    while(iterImg != processingImages.end() && iterMethods != methodsConversionColor.end())
    {
        for(qsizetype y = 0; y < iterImg->height(); ++y)
        {
            QRgb* rgb = reinterpret_cast<QRgb*>(const_cast<uchar*>(iterImg->scanLine(y)));
            for(qsizetype x = 0; x < iterImg->width(); ++x)
            {
                QColor newColor = iterMethods->get()->conversion(QColor(rgb[x]));
                iterImg->setPixelColor(x,y,newColor);
            }
        }

        ++iterImg;
        ++iterMethods;
    }

    emit returnProcessingImages(processingImages);
}

ThreadProcessingImages::~ThreadProcessingImages()
{
    thread.quit();
    thread.wait();
}
