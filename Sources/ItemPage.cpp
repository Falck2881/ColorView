#include "ItemPage.h"
#include "MainWindow.h"
#include "Image.h"
#include <QLabel>
#include <QVBoxLayout>
#include <future>

App::Item::Page::Page(App::MainWindow* const mainWin):
    content(std::make_unique<Content>()),
    tabWidget{std::make_unique<QTabWidget>()},
    mainWindow{mainWin},
    indexOfPage{-1}
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
        // Родительский виджет нужен только для центрирования билборда
        QLabel* parentFrame = new QLabel();

        Fk::Billboard* billboard = new Fk::Billboard(image);
        billboard->setParent(parentFrame);

        QRect rect (tabWidget->width() / 1.4, 20, image.pixmap().width(), image.pixmap().height());
        parentFrame->setFrameRect(rect);

        QVBoxLayout* layout = new QVBoxLayout();
        layout->setAlignment(Qt::AlignVCenter);
        // В родительский виджет упаковываем билборд
        layout->addWidget(billboard);
        parentFrame->setLayout(layout);

        setConnectWithBillboard(billboard);

        // Добавляем родительский виджет
        tabWidget->addTab(parentFrame,"Untiled");
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

void App::Item::Page::setContent(const Fk::Image& fileName)
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
    QLabel* parentFrame = qobject_cast<QLabel*>(tabWidget->widget(tabWidget->currentIndex()));

    Fk::Billboard* currentBillboard = parentFrame->findChild<Fk::Billboard*>();

    if (currentBillboard != nullptr)
    {
        currentBillboard->setImage(img);
        tabWidget->setCurrentIndex(tabWidget->insertTab(tabWidget->currentIndex(), parentFrame, "*"+img.nameFile()));
        saveCurrentIndexOfPage();
    }
}

void App::Item::Page::removeContent(const qint32 index)
{
    content->removeContent(index);
}

void App::Item::Page::addImageIntoBillboardOfPage(const Fk::Image& image)
{
    // Родительский виджет нужен только для центрирования билборда
    QLabel* parentFrame = new QLabel();
    parentFrame->setMaximumSize(tabWidget->width(), tabWidget->height());

    Fk::Billboard* billboard = new Fk::Billboard(image);
    billboard->setParent(parentFrame);

    QRect rect (parentFrame->width() / 1.4 , 5, image.pixmap().width(), image.pixmap().height());
    parentFrame->setFrameRect(rect);

    QVBoxLayout* layout = new QVBoxLayout();
    layout->setAlignment(Qt::AlignVCenter);
    // В родительский виджет упаковываем билборд
    layout->addWidget(billboard);
    parentFrame->setLayout(layout);

    setConnectWithBillboard(billboard);
    tabWidget->setCurrentIndex(tabWidget->addTab(parentFrame, image.nameFile()));
    saveCurrentIndexOfPage();
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
    QLabel* parentFrame = qobject_cast<QLabel*>(tabWidget->widget(tabWidget->currentIndex()));

    Fk::Billboard* currentBillboard = parentFrame->findChild<Fk::Billboard*>();

    if (currentBillboard != nullptr)
        currentBillboard->setPencilBox(pencilBox);
}
