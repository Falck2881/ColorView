#ifndef INITCOLORIMG_H
#define INITCOLORIMG_H

#include "InitializeImg.h"

namespace Fk::Init
{
    class ColorImg: public Fk::Base::InitializeImg
    {
        public:
            ColorImg(const QString nameFileImg);
    };
}
#endif // INITCOLORIMG_H
