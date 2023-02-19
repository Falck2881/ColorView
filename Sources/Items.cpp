#include "Items.h"

App::Base::Item::Item(std::shared_ptr<Content> newContent):
    content(newContent)
{

}
void App::Base::Item::setIndex(const qint32 newIndex)
{
    content->setIndex(newIndex);
}

void App::Base::Item::setContent(std::shared_ptr<Billboard> billboard)
{
    content->setContent(billboard);
}

void App::Base::Item::updateContent(std::shared_ptr<Billboard> billboard)
{
    content->updateContent(billboard);
}
