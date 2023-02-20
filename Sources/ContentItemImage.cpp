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
                         this, &ContentItemImage::setProcessingBillboards);

        ++threadProcessingImg;
    }
}

void ContentItemImage::setProcessingBillboards(std::pair<QVector<Fk::Image>, NumbersThreads> newCompletedBillboardProcessing)
{
    addCompletedBillboardProcessing(newCompletedBillboardProcessing);
    removeOldsProcessingBillboards();

    if(readyProcessingOfBillboard.size() == 3)
    {
        for(auto& processingBillboard: readyProcessingOfBillboard){
               collageProcessingBillboards.append(processingBillboard.first);
        }

        readyProcessingOfBillboard.erase(readyProcessingOfBillboard.constBegin(), readyProcessingOfBillboard.constEnd());
        readyProcessingOfBillboard.squeeze();
    }

}

void ContentItemImage::addCompletedBillboardProcessing(std::pair<QVector<Fk::Image>, NumbersThreads> newCompletedBillboardProcessing)
{
    if(readyProcessingOfBillboard.size() != 3)
    {
        readyProcessingOfBillboard.append(newCompletedBillboardProcessing);
        auto comparation{[](std::pair<QVector<Fk::Image>, NumbersThreads> fPair,
                            std::pair<QVector<Fk::Image>, NumbersThreads> sPair)
                            {
                                return fPair.second < sPair.second;
                            }
                        };

        std::sort(readyProcessingOfBillboard.begin(),readyProcessingOfBillboard.end(),comparation);
    }
}

void ContentItemImage::removeOldsProcessingBillboards()
{
    if(!collageProcessingBillboards.isEmpty())
    {
        collageProcessingBillboards.erase(collageProcessingBillboards.constBegin(), collageProcessingBillboards.constEnd());
        collageProcessingBillboards.squeeze();
    }
}

void ContentItemImage::setContent(std::shared_ptr<Billboard> billboard)
{
    billboards.push_back(billboard);
}

void ContentItemImage::updateContent(std::shared_ptr<Billboard> billboard)
{
    replaceBillboard(billboard);
    Fk::Image currImage = image();

    if(currImage.isHighQuality())
        startThreadsForProcessingImages(currImage);
}


void ContentItemImage::startThreadsForProcessingImages(const Fk::Image& image)
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
