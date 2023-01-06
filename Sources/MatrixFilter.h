#ifndef MATRIXFILTER_H
#define MATRIXFILTER_H

#include <QColor>
#include <array>
#include "AveragingColor.h"

namespace Conversion
{
    class MatrixColor: public ConversionColor
    {
        public:
            MatrixColor(const MatrixColor& oldMatrix);
            MatrixColor(std::array<std::array<float,4>,4> newMAtrix);
            QColor conversion(QColor oldColor) override;
        private:
            std::array<std::array<float,4>,4> matrix;

    };
}

#endif // MATRIXFILTER_H
