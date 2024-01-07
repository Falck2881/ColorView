#include "ItemPage.h"
#include "MainWindow.h"
#include "Image.h"
#include <QLabel>

App::Item::Page::Page(App::MainWindow* const mainWin):
    content(std::make_unique<Content>()),
    tabWidget{std::make_unique<QTabWidget>()},
    mainWindow{mainWin}
{
    mainWindow->appand(this);
    initializeStartPage();
    connectWithCommand();
}

void App::Item::Page::initializeStartPage()
{
    tabWidget->setTabPosition(QTabWidget::North);
    isThereAnyPage();
}

void App::Item::Page::isThereAnyPage()
{
    if(tabWidget->currentIndex() == -1)
    {
        Fk::Image image(":/imgNotFound.png");
        Fk::Billboard* billboard = new Fk::Billboard(image);
        setConnectWithBillboard(billboard);
        tabWidget->addTab(billboard,"Untiled");
        tabWidget->setTabsClosable(false);
    }
}

void App::Item::Page::setConnectWithBillboard(Fk::Billboard* const newBillboard)
{
    QObject::connect(newBillboard, &Fk::Billboard::updateBillboard, this, &App::Item::Page::receiveUpdatedImage);
}

void App::Item::Page::receiveUpdatedImage(Fk::Image image)
{
    content->updateContent(image);
    mainWindow->drawnImageWasModified(image);
}

void App::Item::Page::connectWithCommand()
{
    QObject::connect(tabWidget.get(), &QTabWidget::currentChanged, this, &App::Item::Page::switchPage);
    QObject::connect(tabWidget.get(), &QTabWidget::tabCloseRequested, this, &App::Item::Page::closePage);
}

void App::Item::Page::switchPage()
{
    if(checkIndexOnPage()){
        notifyAllColleagues();
        finishTheJob();
    }
}

bool App::Item::Page::checkIndexOnPage() const
{
    return tabWidget->currentIndex() >= 0 ? true : false;
}

void App::Item::Page::notifyAllColleagues()
{
    if(!content->isBillboardEmpty())
        mainWindow->changeIndex(tabWidget->currentIndex());
}

void App::Item::Page::finishTheJob()
{
    if(!content->isBillboardEmpty())
        mainWindow->changeContentOfItems(this);
}

void App::Item::Page::closePage(const qint32 index)
{
    if(index >= 0){
        mainWindow->closePage(index);
        mainWindow->notifyAboutClosePage(index);
        removeStartPage(index);
        saveCurrentIndexOfPage();
        isThereAnyPage();
        mainWindow->setActivityTheWitgetsInEachObserver();
    }
}

void App::Item::Page::saveCurrentIndexOfPage()
{
    indexOfPage = tabWidget->currentIndex();
}

void App::Item::Page::setIndex(const qint32 newIndex)
{
    content->setIndex(newIndex);
}

void App::Item::Page::setContent(const QString& fileName)
{
    if(content->isBillboardEmpty())
        removeStartPage();

    content->setContent(fileName);

    if(!content->isBillboardEmpty())
        enableTabsClosable();

    addImageIntoBillboardOfPage(content->lastImage());
}

void App::Item::Page::updateContent(const Fk::Image& img)
{
    content->updateContent(img);
    Fk::Billboard* currentBillboard = qobject_cast<Fk::Billboard*>(tabWidget->widget(tabWidget->currentIndex()));
    currentBillboard->setImage(img);

    tabWidget->setCurrentIndex(tabWidget->insertTab(tabWidget->currentIndex(), currentBillboard, "*"+img.nameFile()));
}

void App::Item::Page::removeContent(const qint32 index)
{
    content->removeContent(index);
}

void App::Item::Page::addImageIntoBillboardOfPage(const Fk::Image& image)
{
    Fk::Billboard* billboard = new Fk::Billboard(image);
    setConnectWithBillboard(billboard);
    tabWidget->setCurrentIndex(tabWidget->addTab(billboard, image.nameFile()));
}

QTabWidget* App::Item::Page::getTabWidget() const
{
    return tabWidget.get();
}

Fk::Image App::Item::Page::getImageCurrentPage() const
{
    return content->image();
}

qint32 App::Item::Page::currentIndexOfPage() const
{
    return indexOfPage;
}

void App::Item::Page::removeStartPage(const qint32 index)
{
    if(index >= 0)
        tabWidget->removeTab(index);
}

void App::Item::Page::enableTabsClosable()
{
    tabWidget->setTabsClosable(true);
}

void App::Item::Page::preparePageToDrawing(const Fk::PencilBox& pencilBox)
{
    auto bilboard = qobject_cast<Fk::Billboard*>(tabWidget->widget(tabWidget->currentIndex()));
    bilboard->setPencilBox(pencilBox);
}
