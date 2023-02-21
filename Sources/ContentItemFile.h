#ifndef CONTENTITEMFILE_H
#define CONTENTITEMFILE_H

#include "Content.h"


class ContentItemFile: public Content
{
    public:
        ContentItemFile() = default;
        void setContent(const std::pair<QString,QString>& newContent) override;
        void updateContent(std::shared_ptr<Billboard>) override;

};

#endif // CONTENTITEMFILE_H
