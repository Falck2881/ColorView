#ifndef HISTORY_H
#define HISTORY_H

#include <QList>
#include <concepts>
#include <memory>
#include <assert.h>
#include "Image.h"

template<typename T>
concept isFile = std::same_as<T, Fk::Image>;

namespace FileModified
{
    template<isFile T>
    class History
    {
        public:
            explicit History(T typeFile);
            auto file() const;
            void push_back(T typeFile);
            auto last() const;
            void increment();
            void decrement();
        private:
            qint32 index;
            QList<T> historyEdit;
    };
}

template<isFile T>
FileModified::History<T>::History(T typeFile):index(0)
{
    historyEdit.push_back(typeFile);
}

template<isFile T>
auto FileModified::History<T>::file() const
{
    assert(index >= 0);
    return historyEdit.at(index);
}

template<isFile T>
void FileModified::History<T>::push_back(T typeFile)
{
    historyEdit.push_back(typeFile);
    ++index;
}

template<isFile T>
auto FileModified::History<T>::last() const
{
    assert(!historyEdit.empty());
    return historyEdit.last();
}

template<isFile T>
void FileModified::History<T>::increment()
{
    if(index < historyEdit.size()-1)
        ++index;

}

template<isFile T>
void FileModified::History<T>::decrement()
{
    if(index != 0)
        --index;
}
#endif // HISTORY_H
