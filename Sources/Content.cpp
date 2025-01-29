#include "Content.h"
#include <exception>
#include <QDebug>
#include <assert.h>
#include <future>
//#define NDEBUG

Content::Content():index(-1)
{
}

void Content::updateContent(const Fk::Image& image)
{
    assert(index != -1);

    imageArray.replace(index,image);
}

void Content::setContent(const Fk::Image& content)
{
    imageArray.push_back(content);
}

void Content::removeContent(const qint32 index)
{
    assert(index != -1);
    imageArray.removeAt(index);
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
    return imageArray.isEmpty();
}

const Fk::Image& Content::image() const
{
    assert(index != -1);
    return imageArray.at(index);
}

const Fk::Image& Content::lastImage() const
{
    return imageArray.last();
}

QVector<Fk::Image> Content::images() const
{
    return imageArray;
}

qsizetype Content::sizeBillboard() const
{
    return imageArray.size();
}

void Content::replaceImage(Fk::Image image)
{
    assert(index != -1);

    imageArray.replace(index, image);
}
