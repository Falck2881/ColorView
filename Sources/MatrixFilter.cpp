#include "MatrixFilter.h"
#include <QFile>
#include <QStringList>
#include <QRegularExpression>
#include <QRegularExpressionMatch>

Conversion::MatrixColor::MatrixColor(const MatrixColor& oldMatrix)
{
    this->matrix = oldMatrix.matrix;
}

Conversion::MatrixColor::MatrixColor(std::array<std::array<float,4>,4> newMatrix):
    matrix{newMatrix}
{

}

QColor Conversion::MatrixColor::conversion(const QColor& oldColor)
{
    std::array<float,4> oldRgbaPixel{oldColor.redF(), oldColor.greenF(),
                                oldColor.blueF(), oldColor.alphaF()};
    std::array<float,4> newRgbaPixel{0.0f,0.0f,0.0f,0.0f};

    for(quint32 i = 0; i < matrix.size(); ++i)
    {
        for(quint32 j = 0; j < matrix.size(); ++j)
        {
            newRgbaPixel.at(i) += matrix.at(i).at(j) * oldRgbaPixel.at(i);
            newRgbaPixel.at(i) = qBound(0.0f,newRgbaPixel.at(i),1.0f);
        }
    }

    QColor newColor;
    newColor.setRgbF(newRgbaPixel.at(0), newRgbaPixel.at(1),
                     newRgbaPixel.at(2), newRgbaPixel.at(3));
    return newColor;
}
