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
            Allocation(const std::pair<QString,QString>& newContent);
            std::unique_ptr<Billboard> operator()();
        private:
            bool checkContentPair() const;
            std::unique_ptr<Billboard> make() const;
            std::pair<QString, QString> content;
    };
}
#endif // ALLOCATION_H
