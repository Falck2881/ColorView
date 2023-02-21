#ifndef CONTENTITEMEDIT_H
#define CONTENTITEMEDIT_H

#include "Content.h"

class ContentItemEdit: public Content
{
    public:
        ContentItemEdit() = default;
        void setContent(const std::pair<QString,QString>& newContent) override;
};

#endif // CONTENTITEMEDIT_H
