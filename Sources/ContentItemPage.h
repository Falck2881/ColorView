#ifndef CONTENTITEMPAGE_H
#define CONTENTITEMPAGE_H

#include "Content.h"
#include "ItemPage.h"

class ContentItemPage: public Content
{
    public:
        ContentItemPage(App::Item::Page* const itemPage);
        void updateContent(std::shared_ptr<Billboard> billboard) override;
        void setContent(const std::pair<QString,QString>& newContent) override;
    private:
        void checkStartingPage();
        void createBillboardForPage(const std::pair<QString,QString>& newContent);
    private:
        App::Item::Page* const itemPage;

};

#endif // CONTENTITEMPAGE_H