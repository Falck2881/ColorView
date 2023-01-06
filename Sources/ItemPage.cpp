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
    if(index >= 0)
        mainWindow->changeIndexOnFile(index);
}

void App::Item::Page::updateContant(Fk::Image image)
{
    assert(indexOnFile != -1);

    images.replace(indexOnFile,image);
    auto currentImg = images.at(indexOnFile);

    QLabel* label = qobject_cast<QLabel*>(tabWidget->widget(indexOnFile));
    label->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    label->setPixmap(currentImg.pixmap());
    qint32 indexPage = tabWidget->insertTab(indexOnFile, label, "*"+currentImg.nameFile());
    tabWidget->setCurrentIndex(indexPage);
}

void App::Item::Page::setContant(Fk::Image image)
{
    if(images.empty())
        hideStartPage();

    QLabel* label = new QLabel;
    label->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    label->setPixmap(image.pixmap());

    qint32 indexPage = tabWidget->addTab(label,image.nameFile());
    images.push_back(image);
    tabWidget->setCurrentIndex(indexPage);
}

QTabWidget* App::Item::Page::getTabWidget() const
{
    return tabWidget.get();
}

void App::Item::Page::hideStartPage()
{
    tabWidget->removeTab(START_PAGE);
}

