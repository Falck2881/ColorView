#ifndef HISTORY_H
#define HISTORY_H

#include <QList>
#include <concepts>
#include <memory>
#include <assert.h>
#include "Image.h"

//#define NDEBUG

template<typename T>
concept isImage = std::same_as<T, Fk::Image>;

namespace Modified
{
    namespace Image
    {
        template<isImage T>
        class History
        {
            public:
                explicit History(const T& typeFile);
                auto image() const;
                void push_back(const T& typeFile);
                void erase();
                bool isEmpty() const;
                auto last() const;
                void redo();
                void undo();
            private:
                qint32 index;
                QList<T> historyEdit;
        };
    }
}

template<isImage T>
Modified::Image::History<T>::History(const T& typeFile):index(0)
{
    historyEdit.push_back(typeFile);
}

template<isImage T>
void Modified::Image::History<T>::erase()
{
    if(!historyEdit.isEmpty()){
        historyEdit.erase(historyEdit.cbegin(),historyEdit.cend());
        historyEdit.squeeze();
    }
}

template<isImage T>
auto Modified::Image::History<T>::image() const
{
    assert(index >= 0);
    return historyEdit.at(index);
}

template<isImage T>
void Modified::Image::History<T>::push_back(const T& typeFile)
{
    historyEdit.push_back(typeFile);
    ++index;
}

template<isImage T>
bool Modified::Image::History<T>::isEmpty() const
{
    return historyEdit.isEmpty() ? true : false;
}

template<isImage T>
auto Modified::Image::History<T>::last() const
{
    assert(!historyEdit.empty());
    return historyEdit.last();
}

template<isImage T>
void Modified::Image::History<T>::redo()
{
    if(index < historyEdit.size()-1)
        ++index;

}

template<isImage T>
void Modified::Image::History<T>::undo()
{
    if(index != 0)
        --index;
}
#endif // HISTORY_H
