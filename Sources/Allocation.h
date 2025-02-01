#ifndef ALLOCATION_H
#define ALLOCATION_H

#include "GraphicsImageItem.h"
#include <utility>
#include <memory>

namespace Fk
{
    class Allocation
    {
        public:
            Allocation(const QString& nameFile);
            std::unique_ptr<Fk::GraphicsImageItem> operator()();
        private:
            bool checkContentPair() const;
            std::unique_ptr<Fk::GraphicsImageItem> make() const;
            const QString nameFile;
    };
}
#endif // ALLOCATION_H
