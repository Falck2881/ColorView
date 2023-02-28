#include "Content.h"
#include "Allocation.h"
#include <exception>
#include <QDebug>
#include <assert.h>
//#define NDEBUG

void Content::updateContent(std::shared_ptr<Billboard> board)
{
    assert(index != -1);

    billboards.replace(index,board);
}

void Content::setContent(const QString& content)
{
    Fk::Allocation makeBillboardImage(content);
    billboards.push_back(makeBillboardImage());
}

void Content::removeContent(const qint32 index)
{
    assert(index != -1);
    billboards.removeAt(index);
}

void Content::setIndex(const qint32 newIndex)
{
    try {
        if(newIndex != -1)
            index = newIndex;
        else
            throw std::logic_error("Variable 'newIndex' have value: -1 ");
    }  catch (const std::logic_error& exce) {
        qDebug() << exce.what();
        index = 0;
        throw;
    }
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

void Content::replaceBillboard(std::shared_ptr<Billboard> billboard)
{
    assert(index != -1);

    billboards.replace(index, billboard);
}
