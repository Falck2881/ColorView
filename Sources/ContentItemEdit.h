#ifndef CONTENTITEMEDIT_H
#define CONTENTITEMEDIT_H

#include "Content.h"

class ContentItemEdit: public Content
{
    public:
        ContentItemEdit() = default;
        void setContent(std::shared_ptr<Billboard>) override;
};

#endif // CONTENTITEMEDIT_H
