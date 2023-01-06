#ifndef FILTERBALCKWHITE_H
#define FILTERBALCKWHITE_H

#include "FilterImage.h"

namespace SubFilter
{
    class BalckWhite: public Base::Filter
    {
        public:
            BalckWhite();
        private:
            QColor getColor(const QColor oldColor) override final;
    };
}
#endif // FILTERBALCKWHITE_H
