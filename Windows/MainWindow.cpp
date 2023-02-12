#include "MainWindow.h"
#include <QMenuBar>
#include <QGuiApplication>
#include <QScreen>

App::MainWindow::MainWindow()
{
   initializeItemsApp();
   setGeometryScreen();
}

void App::MainWindow::initializeItemsApp()
{
    itemImage = std::make_unique<App::Item::Image>(this);

    itemFile = std::make_unique<App::Item::File>(this);

    itemEdit = std::make_unique<App::Item::Edit>(this);

    menuBar()->addMenu(itemFile->getMenu());
    addToolBar(Qt::TopToolBarArea,itemFile->getToolBar());

    menuBar()->addMenu(itemEdit->getMenu());
    addToolBar(Qt::TopToolBarArea,itemEdit->getToolBar());
    addToolBarBreak(Qt::TopToolBarArea);

    menuBar()->addMenu(itemImage->getMenu());

    itemPage = std::make_unique<App::Item::Page>(this);
    setCentralWidget(itemPage->getTabWidget());
}

void App::MainWindow::setGeometryScreen()
{
    auto screen = QGuiApplication::primaryScreen();
    quint32 width = screen->size().width();
    quint32 height = screen->size().height();
    this->setGeometry(0,0,width,height);
    this->setMaximumSize(width,height);
    this->setMinimumSize(800,600);
}

void App::MainWindow::appand(App::Base::Item *const observer)
{
    observers.push_back(observer);
}


void App::MainWindow::setFileInEachObserver(const Fk::Image& image)
{
    for(auto obs: observers)
    {
        obs->setContent(image);
        obs->checkStatyActions();
    }
}

void App::MainWindow::changeIndexOnFile(const quint32 index)
{
    for(auto obs: observers){
        obs->saveIndex(index);
        obs->checkStatyActions();
    }
}

void App::MainWindow::updateFileInEachObserver(const Fk::Image& image)
{
    for(auto obs: observers){
        obs->updateContent(image);
    }
}

void App::MainWindow::changesItems(Base::Item* const item)
{
    if(item == itemImage.get())
        itemEdit->saveChangesInHistory(itemImage->getImage());
    else if(item == itemEdit.get())
        updateFileInEachObserver(itemEdit->getCurrentImage());
    else if(item == itemPage.get()){
        itemImage->updateActivityFilter();
    }
}
