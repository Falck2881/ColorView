#include "FilterSaturation.h"

SubFilter::Saturation::Saturation():Base::Filter(this)
{

}

QColor SubFilter::Saturation::getColor(const QColor oldColor)
{
    const quint32 N{3};
    const qreal ratio{0.2};
    qreal newRgb[N]{0,0,0};
    qreal oldRgb[N][1]{{oldColor.redF()},{oldColor.greenF()},{oldColor.blueF()}};



    for(quint32 i = 0; i < N; ++i)
    {
        for(quint32 j = 0; j < N; ++j)
        {
            newRgb[i] += matrix[i][j] * oldRgb[i][j];
            newRgb[j] = qBound(0.0, newRgb[i], 1.0);
        }
    }

    QColor newColor;
    newColor.setRgbF(newRgb[0], newRgb[1], newRgb[2]);
    return newColor;
}
