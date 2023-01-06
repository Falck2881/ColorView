#ifndef CONVERSIONCOLOR_H
#define CONVERSIONCOLOR_H

#include <QColor>

class ConversionColor
{
    public:
        virtual ~ConversionColor() = default;
        virtual QColor conversion(QColor oldColor) = 0;
    protected:
        ConversionColor() = default;
};

#endif // CONVERSIONCOLOR_H
