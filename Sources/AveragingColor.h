#ifndef AVERAGINGCOLOR_H
#define AVERAGINGCOLOR_H

#include "CaluclateColor.h"

class AveragingColor: public Base::CalculateColor
{
    public:
        AveragingColor() = default;
        QColor calculateColor(QColor oldColor) override final;
};

#endif // AVERAGINGCOLOR_H
