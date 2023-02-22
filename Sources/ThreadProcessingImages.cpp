#include "ThreadProcessingImages.h"

ThreadProcessingImages::ThreadProcessingImages()
{
}

void ThreadProcessingImages::setMethodsConversionColor(QVector<std::shared_ptr<ConversionColor>> newMethodsConversionColor)
{
    methodsConversionColor = newMethodsConversionColor;
}

void ThreadProcessingImages::setNumberThread(NumbersThreads numberThread)
{
    currentNumberThread = numberThread;
}

void ThreadProcessingImages::setCopyImage(Fk::Image image)
{
    collageProcessingImages << image << image;
}

bool ThreadProcessingImages::isRun() const
{
    return isRunning();
}

void ThreadProcessingImages::run()
{

    auto processingImage{collageProcessingImages.begin()};
    auto iterMethods{methodsConversionColor.begin()};

    while(processingImage != collageProcessingImages.end() && iterMethods != methodsConversionColor.end())
    {
        for(qsizetype y = 0; y < processingImage->height(); ++y)
        {
            QRgb* rgb = reinterpret_cast<QRgb*>(const_cast<uchar*>(processingImage->scanLine(y)));
            for(qsizetype x = 0; x < processingImage->width(); ++x)
            {
                QColor newColor = iterMethods->get()->conversion(QColor(rgb[x]));
                processingImage->setPixelColor(x,y,newColor);
            }
        }

        ++processingImage;
        ++iterMethods;
    }

    std::pair<QVector<Fk::Image>, NumbersThreads> pair(collageProcessingImages,currentNumberThread);
    removeCollectionProcessingImages();

    if(collageProcessingImages.isEmpty())
        emit returnProcessingImages(pair);
}

void ThreadProcessingImages::removeCollectionProcessingImages()
{
    if(!collageProcessingImages.isEmpty())
    {
        auto begin{collageProcessingImages.constBegin()};
        auto end{collageProcessingImages.constEnd()};
        collageProcessingImages.erase(begin,end);
        collageProcessingImages.squeeze();
    }
}

ThreadProcessingImages::~ThreadProcessingImages()
{
    quit();
    wait();
}
