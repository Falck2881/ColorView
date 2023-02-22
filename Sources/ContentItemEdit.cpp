#include "ContentItemEdit.h"
#include "Allocation.h"

void ContentItemEdit::setContent(const std::pair<QString,QString>& newContent)
{
    Fk::Allocation makeBillboardImage(newContent);
    history.push_back(Modified::Billboard::History<Billboard>{makeBillboardImage()});
}
