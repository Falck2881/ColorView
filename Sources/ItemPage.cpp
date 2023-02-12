#include "ItemPage.h"
#include "MainWindow.h"
#include "Image.h"
#include <QLabel>
#define NDEBUG
#include <assert.h>
#define START_PAGE 0

App::Item::Page::Page(App::MainWindow* const mainWin):
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
        mainWindow->changeIndexOnFile(index);
        mainWindow->changesItems(this);
    }
}

void App::Item::Page::updateContent(const Fk::Image& image)
{
    updatePage(image);
}

void App::Item::Page::updatePage(const Fk::Image& image)
{
    assert(indexOnFile != -1);

    images.replace(indexOnFile,image);
    auto imageCurrentPage = images.at(indexOnFile);

    QLabel* label = qobject_cast<QLabel*>(tabWidget->widget(indexOnFile));
    label->setAlignment(Qt::AlignCenter);
    label->setPixmap(imageCurrentPage.pixmap());

    tabWidget->setCurrentIndex(tabWidget->insertTab(indexOnFile, label, "*"+imageCurrentPage.nameFile()));
}

void App::Item::Page::setContent(const Fk::Image& image)
{
    setImageIntoPage(image);
}

void App::Item::Page::setImageIntoPage(const Fk::Image& image)
{
    if(images.empty())
        hideStartPage();

    QLabel* label = new QLabel;
    label->setAlignment(Qt::AlignCenter);
    label->setPixmap(image.pixmap());

    images.push_back(image);

    if(!images.isEmpty())
        tabWidget->setCurrentIndex(tabWidget->addTab(label,image.nameFile()));
}

QTabWidget* App::Item::Page::getTabWidget() const
{
    return tabWidget.get();
}

Fk::Image App::Item::Page::getImageCurrentPage() const
{
    assert(indexOnFile != -1);
    return images.at(indexOnFile);
}

void App::Item::Page::hideStartPage()
{
    tabWidget->removeTab(START_PAGE);
}

