#include "MainWindow.h"
#include <QMenuBar>
#include <QGuiApplication>
#include <QScreen>
#include <QStatusBar>

App::MainWindow::MainWindow():
    frame{std::make_unique<QLabel>()}
{
   initializeMembersOfClass();

   if(!observers.isEmpty())
        addAllItemsInManinWindow();

   setGeometryScreen();
}

void App::MainWindow::initializeMembersOfClass()
{
    itemImage = std::make_unique<App::Item::Image>(this);

    if(itemImage != nullptr)
        itemPage = std::make_unique<App::Item::Page>(this);

    itemEdit = std::make_unique<App::Item::Edit>(this);
    itemFile = std::make_unique<App::Item::File>(this);
}

void App::MainWindow::addAllItemsInManinWindow()
{
    menuBar()->addMenu(itemFile->getMenu());
    addToolBar(Qt::TopToolBarArea,itemFile->getToolBar());

    menuBar()->addMenu(itemEdit->getMenu());
    addToolBar(Qt::TopToolBarArea,itemEdit->getToolBar());
    addToolBarBreak(Qt::TopToolBarArea);

    menuBar()->addMenu(itemImage->getMenu());

    setCentralWidget(itemPage->getTabWidget());
}

void App::MainWindow::setGeometryScreen()
{
    auto screen = QGuiApplication::primaryScreen()->availableGeometry().size();
    quint32 width = screen.width() * 0.9;
    quint32 height = screen.height() * 0.9;
    this->setGeometry(50,50,width,height);
    this->setMaximumSize(width,height);
    this->setMinimumSize(800,600);
}

void App::MainWindow::appand(Base::Item *const observer)
{
    observers.push_back(observer);
}


void App::MainWindow::setBillboardInEachObserver(const QString& newContent)
{
    for(auto obs: observers)
        obs->setContent(newContent);
}

void App::MainWindow::changeIndex(const qint32 newIndex)
{
    for(auto obs: observers)
        obs->setIndex(newIndex);
}

void App::MainWindow::updateBillboardInEachObserver(std::shared_ptr<Billboard> billboard)
{
    for(auto obs: observers)
        obs->updateContent(billboard);
}

void App::MainWindow::notifyAboutClosePage(const qint32 index)
{
    for(auto obs: observers)
        obs->removeContent(index);
}

void App::MainWindow::setActivityTheWitgetsInEachObserver()
{
    for(auto obs: observers)
        obs->setActivityOfWidgets();
}

void App::MainWindow::changeContentOfItems(Base::Item* const item)
{
    if(item == itemImage.get()){
        itemEdit->saveChangesInHistory(itemImage->getBillboard());
    }
    else if(item == itemEdit.get()){
        updateBillboardInEachObserver(itemEdit->getBillboard());
        setActivityTheWitgetsInEachObserver();
    }
    else if(item == itemPage.get()){
        itemImage->startThreads();
        setActivityTheWitgetsInEachObserver();
    }
}

void App::MainWindow::closePage(const qint32 index)
{
    itemEdit->checkHistoryModified(index);
}

void App::MainWindow::closePageAndSave()
{
    itemFile->saveAs();
}

void App::MainWindow::closePageWithoutSave()
{
    itemFile->save();
}

bool App::MainWindow::observersExist() const
{
    return !observers.empty() ? true:false;
}

void App::MainWindow::updateMessageInStatusBar(App::Base::Item* const item)
{
    if(item == itemFile.get())
        statusBar()->showMessage(itemFile->messageAboutAction(), 1800);
    else if(item == itemEdit.get())
        statusBar()->showMessage(itemEdit->messageAboutAction(), 1800);
    else if(item == itemImage.get())
        statusBar()->showMessage(itemImage->messageAboutAction(), 1800);
    else if(item == itemPage.get())
        statusBar()->showMessage(itemPage->messageAboutAction(), 1800);
}
