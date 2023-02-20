#include "ContentItemPage.h"

ContentItemPage::ContentItemPage(App::Item::Page* const itemPage):
    itemPage(itemPage)
{

}

void ContentItemPage::updateContent(std::shared_ptr<Billboard> billboard)
{
    replaceBillboard(billboard);
    itemPage->updatePage(image());
}

void ContentItemPage::setContent(std::shared_ptr<Billboard> billboard)
{
    if(isBillboardEmpty())
        itemPage->hideStartPage();

    Fk::Image currImage = billboard->toImage();

    QLabel* wgdBillboard{new QLabel};
    wgdBillboard->setAlignment(Qt::AlignCenter);
    wgdBillboard->setPixmap(currImage.pixmap());

    billboards.push_back(billboard);
    itemPage->setImageIntoPage(wgdBillboard,currImage);

}
