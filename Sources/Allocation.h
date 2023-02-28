#ifndef ALLOCATION_H
#define ALLOCATION_H

#include "Billboard.h"
#include <utility>
#include <memory>

namespace Fk
{
    class Allocation
    {
        public:
            Allocation(const QString& nameFile);
            std::unique_ptr<Billboard> operator()();
        private:
            bool checkContentPair() const;
            std::unique_ptr<Billboard> make() const;
            const QString nameFile;
    };
}
#endif // ALLOCATION_H
