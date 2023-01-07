#ifndef MATRIXCALCULATE_H
#define MATRIXCALCULATE_H

#include "CaluclateColor.h"

class MatrixCalculateColor: public Base::CalculateColor
{
    public:
        MatrixCalculateColor(MatrixCalculateColor& oldMethod);
        MatrixCalculateColor(const QString nameFileMatrix);
        ~MatrixCalculateColor();
        QColor calculateColor(QColor oldColor) override final;
    private:
        void highlightsMemoryForMatrix();
        void setMatrixFilter(const QString nameFileMatrix);
        QStringList loadMatrix(const QString nameFileMatrix);
        void setValuesInMatrix(const QStringList& value);
    private:
        qreal matrix[3][3];
};

#endif // MATRIXCALCULATE_H
