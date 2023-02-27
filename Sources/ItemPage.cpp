#include "ItemPage.h"
#include "MainWindow.h"
#include "Image.h"
#include <QLabel>

App::Item::Page::Page(App::MainWindow* const mainWin):
    content(std::make_unique<ContentItemPage>(this)),
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
        QLabel* label = new QLabel;
        label->setAlignment(Qt::AlignCenter);
        label->setPixmap(QPixmap(":/imgNotFound.png"));
        tabWidget->addTab(label,"Untiled");
        tabWidget->setTabsClosable(false);
    }
}

void App::Item::Page::connectWithCommand()
{
    QObject::connect(tabWidget.get(), &QTabWidget::currentChanged, this, &App::Item::Page::switchPage);
    QObject::connect(tabWidget.get(), &QTabWidget::tabCloseRequested, this, &App::Item::Page::closePage);
}

void App::Item::Page::switchPage()
{
    if(checkIndexOnPage()){
        writeNoteAboutAction(QString("Switching on page: ") + QString::number(tabWidget->currentIndex()));
        mainWindow->updateMessageInStatusBar(this);
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
        isThereAnyPage();
        mainWindow->setActivityTheWitgetsInEachObserver();
    }
}

void App::Item::Page::setIndex(const qint32 newIndex)
{
    content->setIndex(newIndex);
}

void App::Item::Page::setContent(const std::pair<QString,QString>& newContent)
{
    content->setContent(newContent);
}

void App::Item::Page::updateContent(std::shared_ptr<Billboard> billboard)
{
    content->updateContent(billboard);
}

void App::Item::Page::removeContent(const qint32 index)
{
    content->removeContent(index);
}

void App::Item::Page::updatePage(const Fk::Image& image)
{
    QLabel* billboard = qobject_cast<QLabel*>(tabWidget->widget(tabWidget->currentIndex()));
    billboard->setAlignment(Qt::AlignCenter);
    billboard->setPixmap(image.pixmap());

    tabWidget->setCurrentIndex(tabWidget->insertTab(tabWidget->currentIndex(), billboard, "*"+image.nameFile()));
}

void App::Item::Page::addBillboardIntoPage(QWidget* const billboard, const Fk::Image& image)
{
    tabWidget->setCurrentIndex(tabWidget->addTab(billboard,image.nameFile()));
}

QTabWidget* App::Item::Page::getTabWidget() const
{
    return tabWidget.get();
}

std::shared_ptr<Fk::Image> App::Item::Page::getImageCurrentPage() const
{
    return std::make_shared<Fk::Image>(content->image());
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
