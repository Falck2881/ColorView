#include "ContentItemPage.h"
#include "Allocation.h"
#include "ItemPage.h"

ContentItemPage::ContentItemPage(App::Item::Page* const itemPage):
    itemPage(itemPage)
{

}

void ContentItemPage::updateContent(std::shared_ptr<Billboard> billboard)
{
    replaceBillboard(billboard);
    itemPage->updatePage(billboard->toImage());
}

void ContentItemPage::setContent(const std::pair<QString,QString>& newContent)
{
    checkStartingPage();
    createBillboardForPage(newContent);
}

void ContentItemPage::checkStartingPage()
{
    if(isBillboardEmpty()){
        itemPage->removeStartPage();
        itemPage->enableTabsClosable();
    }
}

void ContentItemPage::createBillboardForPage(const std::pair<QString,QString>& newContent)
{
    Fk::Allocation makeBillboardImage(newContent);
    auto billboard{makeBillboardImage()};
    Fk::Image image = billboard->toImage();
    billboards.push_back(std::move(billboard));

    QLabel* wgdBillboard{new QLabel};
    wgdBillboard->setAlignment(Qt::AlignCenter);
    wgdBillboard->setPixmap(image.pixmap());

    itemPage->addBillboardIntoPage(wgdBillboard,image);
}
