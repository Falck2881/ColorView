#include "ItemImage.h"
#include "MainWindow.h"
#include <QList>

App::Item::Image::Image(App::MainWindow* const mainWin):
    winFrames{std::make_unique<WinFrames>(this)},
    winFilter{std::make_unique<WinFilter>(this)},
    winProperty{std::make_unique<WinImgProperty>()},
    aDepth{std::make_unique<QAction>("&Depth...")},
    aProperty{std::make_unique<QAction>("&Property...")},
    aFilter{std::make_unique<QAction>("&Filter")},
    aFrame{std::make_unique<QAction>("&Frame...")},
    mImage{std::make_unique<QMenu>("&Image")},
    mainWindow{mainWin}
{
    mainWindow->appand(this);
    initializeEachAction();
    connectWithCommand();
}

void App::Item::Image::initializeEachAction()
{
    aDepth->setWhatsThis("Here can choice depth color");
    aProperty->setWhatsThis("Show property a image");
    aFilter->setWhatsThis("Here can choice a filter for you image");
    aFrame->setWhatsThis("Here can added a frame to you image");

    QList<QAction*> listAction{aDepth.get(),aProperty.get(),aFilter.get(),aFrame.get()};

    for(auto action: listAction){
        action->setEnabled(false);
        mImage->addAction(action);
    }
}

void App::Item::Image::connectWithCommand()
{
    QObject::connect(aProperty.get(), &QAction::triggered,
                     this, &App::Item::Image::showProperty);
    QObject::connect(aFilter.get(), &QAction::triggered,
                     this, &App::Item::Image::changeFilters);
    QObject::connect(aFrame.get(), &QAction::triggered,
                     this, &App::Item::Image::changeFrame);
}


void App::Item::Image::changeDepth()
{

}

void App::Item::Image::showProperty()
{
    assert(indexOnFile != -1);

    Fk::Image image = images.at(indexOnFile);
    winProperty->setPropertyImage(image);
    winProperty->show();
}

void App::Item::Image::changeFilters()
{
    assert(indexOnFile != -1);

    Fk::Image image = images.at(indexOnFile);
    winFilter->updateBySourceImage(image);
    winFilter->show();
}

void App::Item::Image::changeFrame()
{
    assert(indexOnFile != -1);

    Fk::Image image = images.at(indexOnFile);
    winFrames->updateBySourceImage(image);
    winFrames->show();
}

void App::Item::Image::updateFile(Fk::Image image)
{
    assert(indexOnFile != -1);
    images.replace(indexOnFile,image);
}

void App::Item::Image::setFile(Fk::Image image)
{
    images.push_back(image);
}

void App::Item::Image::checkStatyActions()
{
    if(images.empty())
        setPropertActions(false);
    else
        setPropertActions(true);
}

void App::Item::Image::setPropertActions(bool value)
{
     QList<QAction*> listAction{aDepth.get(),aProperty.get(),aFilter.get(),aFrame.get()};

     for(auto action: listAction)
         action->setEnabled(value);
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
