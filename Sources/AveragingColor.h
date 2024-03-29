#ifndef AVERAGINGCOLOR_H
#define AVERAGINGCOLOR_H

#include "ConversionColor.h"

namespace Conversion
{

    class AveragingColor: public ConversionColor
    {
        public:
            AveragingColor() = default;
            QColor conversion(const QColor& oldColor) override;
    };
}
#endif // AVERAGINGCOLOR_H
