#include "Content.h"
#include <any>
#include <assert.h>
//#define NDEBUG

Content::Content():index(0)
{

}

void Content::setIndex(const qint32 newIndex)
{
    assert(index != -1);

    index = newIndex;
}

bool Content::isBillboardEmpty() const
{
    return billboards.isEmpty();
}

Fk::Image Content::image() const
{
    assert(index != -1);
    return billboards.at(index)->toImage();
}


QVector<Fk::Image> Content::images() const
{
    QVector<Fk::Image> images;
    for(auto billboard{billboards.begin()}; billboard != billboards.end(); ++billboard)
        images.push_back(billboard->get()->toImage());

    return images;
}

qsizetype Content::sizeBillboard() const
{
    return billboards.size();
}

void Content::saveModifiedOnBillboard(std::shared_ptr<Billboard> billboard)
{
    assert(index != -1);

    history[index].push_back(billboard);
}


auto Content::historyAllBillboard() const
{
    return history;
}

bool Content::isHistoryEmpty() const
{
    return history.isEmpty();
}

void Content::undoModification()
{
    assert(index != -1);

    history[index].undo();
}

void Content::redoModification()
{
    assert(index != -1);

    history[index].redo();
}


std::shared_ptr<Billboard> Content::billboardInHistory() const
{
    assert(index != -1);

    return history.at(index).billboard();}

std::shared_ptr<Billboard> Content::lastModifiedOnBillboard() const
{
    assert(index != -1);

    return history[index].last();
}

void Content::replaceBillboard(std::shared_ptr<Billboard> billboard)
{
    assert(index != -1);

    billboards.replace(index, billboard);
}

QVector<Fk::Image> Content::collageOfImages() const
{
    return collageProcessingBillboards;
}
