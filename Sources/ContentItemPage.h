#ifndef CONTENTITEMPAGE_H
#define CONTENTITEMPAGE_H

#include "Content.h"

namespace App::Item{
class Page;
}

class ContentItemPage: public Content
{
    public:
        ContentItemPage(App::Item::Page* const itemPage);
        void updateContent(std::shared_ptr<Fk::Image> image) override;
    private:
        App::Item::Page* const itemPage;

};

#endif // CONTENTITEMPAGE_H
