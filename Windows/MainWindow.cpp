#include "MainWindow.h"
#include <QMenuBar>
#include <QGuiApplication>
#include <QScreen>
#include <QStatusBar>
#include <QSplitterHandle>
#include <QObject>

App::MainWindow::MainWindow()
{
   initializeMembersOfClass();

   if(!observers.isEmpty())
        addAllItemsInManinWindow();

   setGeometryScreen();
   setCursor(QCursor(QPixmap(":/Normal/cursor.png")));
   setAttribute( Qt::WA_AcceptDrops, true );
   setConnectWithApplicationItems();
}

void App::MainWindow::initializeMembersOfClass()
{
    itemImage = std::make_unique<App::Item::Image>(this);

    if(itemImage != nullptr)
        itemPage = std::make_unique<App::Item::Page>(this);

    itemEdit = std::make_unique<App::Item::Edit>(this);
    itemFile = std::make_unique<App::Item::File>(this);
    itemDrawingTools = std::make_unique<App::Item::DrawingTools>();
}

void App::MainWindow::addAllItemsInManinWindow()
{
    menuBar()->addMenu(itemFile->getMenu());
    addToolBar(Qt::TopToolBarArea,itemFile->getToolBar());

    menuBar()->addMenu(itemEdit->getMenu());
    addToolBar(Qt::TopToolBarArea, itemEdit->getToolBar());
    addToolBar(Qt::TopToolBarArea, itemDrawingTools->getToolBar());
    addToolBarBreak(Qt::TopToolBarArea);

    menuBar()->addMenu(itemImage->getMenu());

    setCentralWidget(itemPage->getTabWidget());
}

void App::MainWindow::setGeometryScreen()
{
    auto screen = QGuiApplication::primaryScreen()->availableGeometry().size();
    quint32 width = screen.width();
    quint32 height = screen.height();
    this->setGeometry(0,0,width,height);
    this->setMaximumSize(width,height);
    this->setMinimumSize(800,600);
}

void App::MainWindow::setConnectWithApplicationItems()
{
    QObject::connect(itemDrawingTools.get(), &App::Item::DrawingTools::toolsHaveBeenUpdate, this, &App::MainWindow::updateDrawingToolsOnPage);

    QObject::connect(itemFile.get(), &App::Item::File::createNewFileImage, this, &App::MainWindow::addImage);
}

void App::MainWindow::appand(Base::Item *const observer)
{
    observers.push_back(observer);
}

void App::MainWindow::setBillboardInEachObserver(const Fk::Image& newContent)
{
    for(auto obs: observers)
        obs->setContent(newContent);
}

void App::MainWindow::changeIndex(const qint32 newIndex)
{
    for(auto obs: observers)
        obs->setIndex(newIndex);
}

void App::MainWindow::updateImageInEachObserver(const Fk::Image& image)
{
    for(auto obs: observers)
        obs->updateContent(image);
}

void App::MainWindow::notifyAboutClosePage(const qint32 index)
{
    for(auto obs: observers)
        obs->removeContent(index);
}

void App::MainWindow::setActivityTheWitgetsInEachObserver()
{
    if(itemPage->currentIndexOfPage() != -1)
        itemDrawingTools->setActivateToolsDrawing(true);
    else
        itemDrawingTools->setActivateToolsDrawing(false);

    for(auto obs: observers)
        obs->setActivityOfWidgets();
}

void App::MainWindow::changeContentOfItems(Base::Item* const item)
{
    if(item == itemImage.get()){
        itemEdit->saveModifiedImageInHistory(itemImage->getImage());
    }
    else if(item == itemEdit.get()){
        updateImageInEachObserver(itemEdit->getImage());
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
    if(item == itemEdit.get())
        statusBar()->showMessage(itemEdit->messageAboutAction(), 2800);
    else if(item == itemImage.get())
        statusBar()->showMessage(itemImage->messageAboutAction(), 2800);
    else if(item == itemPage.get())
        statusBar()->showMessage(itemPage->messageAboutAction(), 2800);
}

void App::MainWindow::updateDrawingToolsOnPage()
{
    itemPage->preparePageToDrawing(itemDrawingTools->getPencilBox());
}

void App::MainWindow::addImage()
{
    Fk::Image image("Undefined");
    setBillboardInEachObserver(image);
    setActivityTheWitgetsInEachObserver();
}

void App::MainWindow::drawnImageWasModified(const Fk::Image& image)
{
    itemEdit->saveDrawnImageModified(image);
    updateImageInEachObserver(itemEdit->getImage());
}
