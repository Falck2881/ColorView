#include "ContentItemEdit.h"
#include "Allocation.h"
#include <QDebug>
#include <assert.h>
//#define NDEBUG

void ContentItemEdit::setIndex(const qint32 newIndex)
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

void ContentItemEdit::saveModifiedOnBillboard(std::shared_ptr<Billboard> billboard)
{
    assert(index != -1);

    history[index].push_back(billboard);
}

Modified::Billboard::History<Billboard> ContentItemEdit::atHistory(const qint32 index) const
{
    return history.at(index);
}

bool ContentItemEdit::isHistoryEmpty() const
{
    return history.isEmpty();
}

void ContentItemEdit::undoModification()
{
    assert(index != -1);

    history[index].undo();
}

void ContentItemEdit::redoModification()
{
    assert(index != -1);

    history[index].redo();
}

std::shared_ptr<Billboard> ContentItemEdit::billboardInHistory() const
{
    assert(index != -1);

    return history.at(index).billboard();
}

std::shared_ptr<Billboard> ContentItemEdit::lastModifiedOnBillboard() const
{
    assert(index != -1);

    return history[index].last();
}

void ContentItemEdit::setContent(const QString& newContent)
{
    Fk::Allocation makeBillboardImage(newContent);
    history.push_back(Modified::Billboard::History<Billboard>{makeBillboardImage()});
}

void ContentItemEdit::removeContent(const qint32 index)
{
    assert(index != -1);

    history[index].erase();
    history.removeAt(index);

    if(isHistoryEmpty()){
        history.squeeze();
    }
}
