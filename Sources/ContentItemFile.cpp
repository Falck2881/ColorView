#include "ContentItemFile.h"
#include <assert.h>
//#define NDEBUG

void ContentItemFile::updateContent(std::shared_ptr<Billboard> board)
{
    assert(index != -1);

    billboards.replace(index,board);
}

void ContentItemFile::setContent(std::shared_ptr<Billboard> board)
{
    billboards.push_back(board);
}
