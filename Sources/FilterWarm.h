#ifndef FILTERWARM_H
#define FILTERWARM_H

#include "FilterImage.h"

namespace SubFilter
{

    class Warm: public Base::Filter
    {
        public:
            Warm();
        private:
            QColor getColor(const QColor oldColor) override final;
    };
}
#endif // FILTERWARM_H
