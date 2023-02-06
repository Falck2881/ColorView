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
    collectionProcessingImages << image << image;
}

bool ThreadProcessingImages::isRun() const
{
    return isRunning();
}

void ThreadProcessingImages::run()
{

    auto processingImage{collectionProcessingImages.begin()};
    auto iterMethods{methodsConversionColor.begin()};

    while(processingImage != collectionProcessingImages.end() && iterMethods != methodsConversionColor.end())
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

    std::pair<QVector<Fk::Image>, NumbersThreads> pair(collectionProcessingImages,currentNumberThread);
    removeCollectionProcessingImages();

    if(collectionProcessingImages.isEmpty())
        emit returnProcessingImages(pair);
}

void ThreadProcessingImages::removeCollectionProcessingImages()
{
    if(!collectionProcessingImages.isEmpty())
    {
        auto begin{collectionProcessingImages.constBegin()};
        auto end{collectionProcessingImages.constEnd()};
        collectionProcessingImages.erase(begin,end);
        collectionProcessingImages.squeeze();
    }
}

ThreadProcessingImages::~ThreadProcessingImages()
{
    quit();
    wait();
}
