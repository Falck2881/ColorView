#include "ContentItemPage.h"
#include "Allocation.h"

ContentItemPage::ContentItemPage(App::Item::Page* const itemPage):
    itemPage(itemPage)
{

}

void ContentItemPage::updateContent(std::shared_ptr<Billboard> billboard)
{
    replaceBillboard(billboard);
    itemPage->updatePage(image());
}

void ContentItemPage::setContent(const std::pair<QString,QString>& newContent)
{
    checkStartingPage();
    createBillboardForPage(newContent);
}

void ContentItemPage::checkStartingPage()
{
    if(isBillboardEmpty())
        itemPage->hideStartPage();
}

void ContentItemPage::createBillboardForPage(const std::pair<QString,QString>& newContent)
{
    //Fk::Allocation makeBillboardImage(newContent);
    auto billboard = std::make_unique<Fk::Image>(newContent.first,newContent.second.toLatin1().data());
    Fk::Image curr = billboard->toImage();
    QLabel* wgdBillboard{new QLabel};
    wgdBillboard->setAlignment(Qt::AlignCenter);
    wgdBillboard->setPixmap(curr.pixmap());

    billboards.push_back(std::move(billboard));
    itemPage->setImageIntoPage(wgdBillboard,curr);
}
