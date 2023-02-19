#ifndef HISTORY_H
#define HISTORY_H

#include <QList>
#include <concepts>
#include <memory>
#include <assert.h>
#include "Image.h"
#define NDEBUG

template<typename T>
concept isBillboard = std::same_as<T, Billboard>;

namespace Modified
{
    namespace Billboard {


        template<isBillboard T>
        class History
        {
            public:
                explicit History(std::shared_ptr<T> typeFile);
                auto billboard() const;
                void push_back(std::shared_ptr<T> typeFile);
                auto last() const;
                void redo();
                void undo();
            private:
                qint32 index;
                QList<std::shared_ptr<T>> historyEdit;
        };
    }
}

template<isBillboard T>
Modified::Billboard::History<T>::History(std::shared_ptr<T> typeFile):index(0)
{
    historyEdit.push_back(typeFile);
}

template<isBillboard T>
auto Modified::Billboard::History<T>::billboard() const
{
    assert(index >= 0);
    return historyEdit.at(index);
}

template<isBillboard T>
void Modified::Billboard::History<T>::push_back(std::shared_ptr<T> typeFile)
{
    historyEdit.push_back(typeFile);
    ++index;
}

template<isBillboard T>
auto Modified::Billboard::History<T>::last() const
{
    assert(!historyEdit.empty());
    return historyEdit.last();
}

template<isBillboard T>
void Modified::Billboard::History<T>::redo()
{
    if(index < historyEdit.size()-1)
        ++index;

}

template<isBillboard T>
void Modified::Billboard::History<T>::undo()
{
    if(index != 0)
        --index;
}
#endif // HISTORY_H
