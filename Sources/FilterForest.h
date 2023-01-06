#ifndef FILTERFOREST_H
#define FILTERFOREST_H

#include "FilterImage.h"

namespace SubFilter
{
    class Forest: public Base::Filter
    {
        public:
            Forest();
        private:
            QColor getColor(const QColor oldColor) override final;
    };
}
#endif // FILTERFOREST_H
