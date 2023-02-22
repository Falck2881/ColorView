#include "ItemPage.h"
#include "MainWindow.h"
#include "Image.h"
#include "ContentItemPage.h"
#include <QLabel>
#define START_PAGE 0

App::Item::Page::Page(App::MainWindow* const mainWin):
    App::Base::Item(std::make_unique<ContentItemPage>(this)),
    tabWidget{std::make_unique<QTabWidget>()},
    mainWindow{mainWin},
    indexOnPage(0)
{
    mainWindow->appand(this);
    initializeStartPage();
    connectWithCommand();
}

void App::Item::Page::initializeStartPage()
{
    tabWidget->setTabPosition(QTabWidget::North);
    QLabel* label = new QLabel;
    label->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    label->setPixmap(QPixmap(":/imgNotFound.png"));
    tabWidget->addTab(label,"Untiled");
}

void App::Item::Page::connectWithCommand()
{
    QObject::connect(tabWidget.get(), &QTabWidget::currentChanged, this, &App::Item::Page::currentPage);
}

void App::Item::Page::currentPage(const qint32 index)
{
    if(index >= 0){
        indexOnPage = index;
        mainWindow->changeIndexOnFile(index);
        mainWindow->changesItems(this);
    }
}

void App::Item::Page::updatePage(const Fk::Image& image)
{

    QLabel* billboard = qobject_cast<QLabel*>(tabWidget->widget(indexOnPage));
    billboard->setAlignment(Qt::AlignCenter);
    billboard->setPixmap(image.pixmap());

    tabWidget->setCurrentIndex(tabWidget->insertTab(indexOnPage, billboard, "*"+image.nameFile()));
}

void App::Item::Page::setImageIntoPage(QWidget* const billboard, const Fk::Image& image)
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

void App::Item::Page::hideStartPage()
{
    tabWidget->removeTab(START_PAGE);
}

