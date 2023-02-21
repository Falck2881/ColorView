#include "ContentItemFile.h"
#include "Allocation.h"
#include <assert.h>
//#define NDEBUG

void ContentItemFile::updateContent(std::shared_ptr<Billboard> board)
{
    assert(index != -1);

    billboards.replace(index,board);
}

void ContentItemFile::setContent(const std::pair<QString,QString>& newContent)
{
    //Fk::Allocation makeBillboardImage(newContent);
    billboards.push_back(std::make_unique<Fk::Image>(newContent.first,newContent.second.toLatin1().data()));
}
