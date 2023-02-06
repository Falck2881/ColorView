#include "ItemImage.h"
#include "MainWindow.h"
#include "ThreadProcessingImages.h"
#include <QList>
#include <algorithm>
//#define NDEBUG
#include <assert.h>
#include <QObject>

App::Item::Image::Image(App::MainWindow* const mainWin):
    winFrames{std::make_unique<WinFrames>(this)},
    winFilter{std::make_unique<WinFilter>(this)},
    winProperty{std::make_unique<WinImgProperty>()},
    mDepthColor{std::make_unique<QMenu>("&Depth Color...")},
    aDepth256Color{std::make_unique<QAction>("256 - Color")},
    aDepth16Color{std::make_unique<QAction>("16 - High Color")},
    aDepth24Color{std::make_unique<QAction>("24 - True Color")},
    aDepth32Color{std::make_unique<QAction>("32 - Color")},
    aProperty{std::make_unique<QAction>("&Property...")},
    aFilter{std::make_unique<QAction>("&Filter")},
    aFrame{std::make_unique<QAction>("&Frame...")},
    mImage{std::make_unique<QMenu>("&Image")},
    mainWindow{mainWin}
{
    mainWindow->appand(this);
    moveConversionsColorIntoThreads();
    initializeSubItemDepth();
    initializeSubItemImage();
    connect();
}

void App::Item::Image::moveConversionsColorIntoThreads()
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

void App::Item::Image::initializeSubItemDepth()
{
    mDepthColor->setWhatsThis("Here you can choice depth color");

    QVector<QAction*> depthColors{aDepth256Color.get(),aDepth16Color.get(),aDepth24Color.get(),aDepth32Color.get()};

    for(auto depth: depthColors){
        depth->setCheckable(true);
        depth->setChecked(false);
        mDepthColor->addAction(depth);
    }

}

void App::Item::Image::initializeSubItemImage()
{
    mDepthColor->setEnabled(false);
    mImage->addMenu(mDepthColor.get());
    aProperty->setWhatsThis("Show property a image");
    aFilter->setWhatsThis("Here can choice a filter for you image");
    aFrame->setWhatsThis("Here can added a frame to you image");

    QList<QAction*> listAction{aProperty.get(),aFilter.get(),aFrame.get()};

    for(auto action: listAction){
        action->setEnabled(false);
        mImage->addAction(action);
    }
}

void App::Item::Image::connect()
{
    QObject::connect(aDepth256Color.get(), &QAction::triggered,
                     this, &App::Item::Image::changeDepth256Color);

    QObject::connect(aDepth256Color.get(), &QAction::triggered,
                     aFilter.get(), &QAction::setDisabled);

    QObject::connect(aDepth256Color.get(), &QAction::triggered,
                     aFrame.get(), &QAction::setDisabled);

    QObject::connect(aDepth16Color.get(), &QAction::triggered,
                     this, &App::Item::Image::changeDepth16Color);

    QObject::connect(aDepth16Color.get(), &QAction::triggered,
                     aFilter.get(), &QAction::setDisabled);

    QObject::connect(aDepth16Color.get(), &QAction::triggered,
                     aFrame.get(), &QAction::setEnabled);

    QObject::connect(aDepth24Color.get(), &QAction::triggered,
                     this, &App::Item::Image::changeDepth24Color);

    QObject::connect(aDepth24Color.get(), &QAction::triggered,
                     aFilter.get(), &QAction::setEnabled);

    QObject::connect(aDepth24Color.get(), &QAction::triggered,
                     aFrame.get(), &QAction::setEnabled);

    QObject::connect(aDepth32Color.get(), &QAction::triggered,
                     this, &App::Item::Image::changeDepth32Color);

    QObject::connect(aDepth32Color.get(), &QAction::triggered,
                     aFilter.get(), &QAction::setEnabled);

    QObject::connect(aDepth32Color.get(), &QAction::triggered,
                     aFrame.get(), &QAction::setEnabled);

    QObject::connect(aProperty.get(), &QAction::triggered,
                     this, &App::Item::Image::showProperty);

    QObject::connect(aFilter.get(), &QAction::triggered,
                     this, &App::Item::Image::changeFilters);

    QObject::connect(aFrame.get(), &QAction::triggered,
                     this, &App::Item::Image::changeFrame);

    auto threadProcessingImg{threadsProcessingImages.begin()};

    while(threadProcessingImg != threadsProcessingImages.end())
    {
        QObject::connect(threadProcessingImg->get(), &ThreadProcessingImages::returnProcessingImages,
                         this, &App::Item::Image::setProcessingImages);

        ++threadProcessingImg;
    }
}

void App::Item::Image::changeDepth256Color()
{
    assert(indexOnFile != -1);

    modifiedImage = collectionSourceImages.at(indexOnFile);
    modifiedImage.setDepthColor(QImage::Format_Indexed8);
    aDepth16Color->setChecked(false);
    aDepth24Color->setChecked(false);
    aDepth32Color->setChecked(false);

    mainWindow->changesItems(this);
}

void App::Item::Image::changeDepth16Color()
{
    assert(indexOnFile != -1);

    modifiedImage = collectionSourceImages.at(indexOnFile);
    modifiedImage.setDepthColor(QImage::Format_RGB16);
    aDepth256Color->setChecked(false);
    aDepth24Color->setChecked(false);
    aDepth32Color->setChecked(false);

    mainWindow->changesItems(this);
}

void App::Item::Image::changeDepth24Color()
{
    assert(indexOnFile != -1);

    modifiedImage = collectionSourceImages.at(indexOnFile);
    modifiedImage.setDepthColor(QImage::Format_RGB888);
    aDepth256Color->setChecked(false);
    aDepth16Color->setChecked(false);
    aDepth32Color->setChecked(false);

    mainWindow->changesItems(this);
}

void App::Item::Image::changeDepth32Color()
{
    assert(indexOnFile != -1);

    modifiedImage = collectionSourceImages.at(indexOnFile);
    modifiedImage.setDepthColor(QImage::Format_RGB32);
    aDepth256Color->setChecked(false);
    aDepth16Color->setChecked(false);
    aDepth24Color->setChecked(false);

    mainWindow->changesItems(this);
}

void App::Item::Image::showProperty()
{
    assert(indexOnFile != -1);

    Fk::Image image = collectionSourceImages.at(indexOnFile);
    winProperty->setPropertyImage(image);
    winProperty->show();
}

void App::Item::Image::changeFilters()
{
    assert(indexOnFile != -1);

    Fk::Image image = collectionSourceImages.at(indexOnFile);
    winFilter->setCollectionProcessingImage(collectionProcessingImage);
    winFilter->updateContant(image);
    winFilter->show();
}

void App::Item::Image::changeFrame()
{
    assert(indexOnFile != -1);

    Fk::Image image = collectionSourceImages.at(indexOnFile);
    winFrames->updateBySourceImage(image);
    winFrames->show();
}

void App::Item::Image::updateContant(Fk::Image image)
{
    assert(indexOnFile != -1);
    replaceImage(image);

    if(isImageHightQuality(image))
        startThreadProcessingImages(image);

}

void App::Item::Image::replaceImage(const Fk::Image& image)
{
    assert(indexOnFile != -1);
    collectionSourceImages.replace(indexOnFile,image);
}

void App::Item::Image::startThreadProcessingImages(const Fk::Image &image)
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

void App::Item::Image::setProcessingImages(std::pair<QVector<Fk::Image>, NumbersThreads> newCompletedImageProcessing)
{
    addToCompleteImageProcessing(newCompletedImageProcessing);
    removeOldsProcessingImages();

    if(completedImageProcessing.size() == 3)
    {
        for(auto& processingImage: completedImageProcessing){
               collectionProcessingImage.append(processingImage.first);
        }

        completedImageProcessing.erase(completedImageProcessing.constBegin(), completedImageProcessing.constEnd());
        completedImageProcessing.squeeze();
    }

}

void App::Item::Image::addToCompleteImageProcessing(std::pair<QVector<Fk::Image>, NumbersThreads> newCompletedImageProcessing)
{
    if(completedImageProcessing.size() != 3)
    {
        completedImageProcessing.append(newCompletedImageProcessing);
        auto comparation{[](std::pair<QVector<Fk::Image>, NumbersThreads> fPair,
                            std::pair<QVector<Fk::Image>, NumbersThreads> sPair)
                            {
                                return fPair.second < sPair.second;
                            }
                        };

        std::sort(completedImageProcessing.begin(),completedImageProcessing.end(),comparation);
    }
}

void App::Item::Image::removeOldsProcessingImages()
{
    if(!collectionProcessingImage.isEmpty())
    {
        collectionProcessingImage.erase(collectionProcessingImage.constBegin(), collectionProcessingImage.constEnd());
        collectionProcessingImage.squeeze();
    }
}

void App::Item::Image::setContant(Fk::Image image)
{
    collectionSourceImages.push_back(image); 

    if(isImageHightQuality(image)){
        aFilter->setEnabled(true);
        aFrame->setEnabled(true);
        startThreadProcessingImages(image);
    }
    else if(image.numberBitOnPix() == "16")
        aFilter->setEnabled(false);
    else if(image.numberBitOnPix() == "8"){
        aFilter->setEnabled(false);
        aFrame->setEnabled(false);
    }

}

void App::Item::Image::checkStatyActions()
{
    if(collectionSourceImages.empty())
        setPropertActions(false);
    else
        setPropertActions(true);

 }

void App::Item::Image::setPropertActions(bool value)
{
    mDepthColor->setEnabled(value);
    aProperty->setEnabled(value);
}

bool App::Item::Image::isImageHightQuality(Fk::Image image) const
{
    return image.numberBitOnPix() == "24" ||
           image.numberBitOnPix() == "32" ?true:false;
}

QMenu* App::Item::Image::getMenu() const
{
    return mImage.get();
}

void App::Item::Image::saveModifiedImage(QWidget *const widget)
{
    if(widget == winFilter.get()){
        modifiedImage = winFilter->getModifiedImage();
        mainWindow->changesItems(this);
    }
    else if(widget == winFrames.get())
    {
        modifiedImage = winFrames->getModifiedImage();
        mainWindow->changesItems(this);
    }
}

Fk::Image App::Item::Image::getImage() const
{
    return modifiedImage;
}

void App::Item::Image::updateActivityFilter()
{
    assert(indexOnFile != -1);

    Fk::Image image = collectionSourceImages.at(indexOnFile);
    if(isImageHightQuality(image)){
        aFilter->setEnabled(true);
        aFrame->setEnabled(true);
        startThreadProcessingImages(image);
    }
    else if(image.numberBitOnPix() == "16")
        aFilter->setEnabled(false);
    else if(image.numberBitOnPix() == "8"){
        aFilter->setEnabled(false);
        aFrame->setEnabled(false);
    }
}
