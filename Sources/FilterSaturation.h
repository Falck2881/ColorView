#ifndef FILTERSATURATION_H
#define FILTERSATURATION_H

#include "FilterImage.h"

namespace SubFilter
{
    class Saturation: public Base::Filter
    {
        public:
            Saturation();
        private:
            QColor getColor(const QColor oldColor);
    };
}

#endif // FILTERSATURATION_H
