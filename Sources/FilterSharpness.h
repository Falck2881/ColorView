#ifndef FILTERSHARPNESS_H
#define FILTERSHARPNESS_H

#include "FilterImage.h"

namespace SubFilter
{
    class Sharpness: public Base::Filter
    {
        public:
            Sharpness();
        private:
            QColor getColor(const QColor oldColor);
    };
}
#endif // FILTERSHARPNESS_H
