#include "Items.h"

App::Base::Item::Item(std::shared_ptr<Content> newContent):
    content(newContent)
{

}
void App::Base::Item::setIndex(const qint32 newIndex)
{
    content->setIndex(newIndex);
}

void App::Base::Item::setContent(const std::pair<QString,QString>& newContent)
{
    content->setContent(newContent);
}

void App::Base::Item::updateContent(std::shared_ptr<Billboard> billboard)
{
    content->updateContent(billboard);
}
