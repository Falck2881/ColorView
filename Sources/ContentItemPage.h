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
        void updateContent(std::shared_ptr<Billboard> billboard) override;
        void setContent(const QString& nameFile) override;
    private:
        void checkStartingPage();
        void createBillboardForPage(const QString& newContent);
    private:
        App::Item::Page* const itemPage;

};

#endif // CONTENTITEMPAGE_H
