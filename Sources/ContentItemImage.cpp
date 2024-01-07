#include "ContentItemImage.h"
#include <assert.h>
//#define NDEBUG

ContentItemImage::ContentItemImage()
{
    moveConversionsColorIntoThreads();
    connect();
}

void ContentItemImage::moveConversionsColorIntoThreads()
{
    QVector<std::shared_ptr<ConversionColor>> methodsConversionColor{collection.getFilters()};
    QVector<NumbersThreads> numbersThreads{NumbersThreads::FIRST_THREAD,
                                           NumbersThreads::SECOND_THREAD,
                                           NumbersThreads::THIRD_THREAD};

    qsizetype indexA{0};
    qsizetype indexB{0};

    while(indexA < numbersThreads.size())
    {
        threadsProcessingImages.push_back(std::make_shared<ThreadProcessingImages>());
        threadsProcessingImages.at(indexA)->setNumberThread(numbersThreads.at(indexA));
        QVector<std::shared_ptr<ConversionColor>> copyMethodsConversionColor;

        while(indexB < methodsConversionColor.size())
        {
            if(indexB <= 1){
                copyMethodsConversionColor.push_back(methodsConversionColor.at(indexB));
                if(indexB == 1) break;
            }
            else if(indexB <= 3){
                copyMethodsConversionColor.push_back(methodsConversionColor.at(indexB));
                if(indexB == 3) break;
            }
            else if(indexB <= 5){
                copyMethodsConversionColor.push_back(methodsConversionColor.at(indexB));
                if(indexB == 5) break;
            }
            ++indexB;
        }

        threadsProcessingImages.at(indexA)->setMethodsConversionColor(copyMethodsConversionColor);
        ++indexA;
        ++indexB;
    }
}


void ContentItemImage::connect()
{
    auto threadProcessingImg{threadsProcessingImages.begin()};

    while(threadProcessingImg != threadsProcessingImages.end())
    {
        QObject::connect(threadProcessingImg->get(), &ThreadProcessingImages::returnProcessingImages,
                         this, &ContentItemImage::setProcessingImage);

        ++threadProcessingImg;
    }
}

void ContentItemImage::setProcessingImage(std::pair<QVector<Fk::Image>, NumbersThreads> newCompletedImageProcessing)
{
    addCompletedImageProcessing(newCompletedImageProcessing);
    removeOldsProcessingImage();

    if(readyProcessingOfImages.size() == 3)
    {
        for(auto& processingImage: readyProcessingOfImages){
               collageProcessingImages.append(processingImage.first);
        }

        readyProcessingOfImages.erase(readyProcessingOfImages.constBegin(), readyProcessingOfImages.constEnd());
        readyProcessingOfImages.squeeze();
    }

}

void ContentItemImage::addCompletedImageProcessing
(std::pair<QVector<Fk::Image>, NumbersThreads> newCompletedBillboardProcessing)
{
    if(readyProcessingOfImages.size() != 3)
    {
        readyProcessingOfImages.append(newCompletedBillboardProcessing);
        auto comparation{[](const std::pair<QVector<Fk::Image>, NumbersThreads>& fPair,
                            const std::pair<QVector<Fk::Image>, NumbersThreads>& sPair)
                            {
                                return fPair.second < sPair.second;
                            }
                        };

        std::sort(readyProcessingOfImages.begin(),readyProcessingOfImages.end(),comparation);
    }
}

void ContentItemImage::removeOldsProcessingImage()
{
    if(!collageProcessingImages.isEmpty())
    {
        collageProcessingImages.erase(collageProcessingImages.constBegin(), collageProcessingImages.constEnd());
        collageProcessingImages.squeeze();
    }
}

void ContentItemImage::updateContent(const Fk::Image& img)
{
    Content::updateContent(img);
    Fk::Image currImage = image();

    if(currImage.is24BitsOnPixel() || currImage.is32BitsOnPixel())
        std::async(std::launch::async , &ContentItemImage::startThreads, this, currImage);
}


void ContentItemImage::startThreads(const Fk::Image& image)
{
    auto threadProcessingImage{threadsProcessingImages.begin()};

    while(threadProcessingImage != threadsProcessingImages.end())
    {
        if(!threadProcessingImage->get()->isRun()){
            threadProcessingImage->get()->setCopyImage(image);
            threadProcessingImage->get()->start();
        }
        ++threadProcessingImage;
    }
}

QVector<Fk::Image> ContentItemImage::collageOfImages() const
{
    return collageProcessingImages;
}
