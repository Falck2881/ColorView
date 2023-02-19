#include "ContentItemEdit.h"


void ContentItemEdit::setContent(std::shared_ptr<Billboard> board)
{
    history.push_back(Modified::Billboard::History<Billboard>{board});
}
