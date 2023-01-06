#include "FilterBalckWhite.h"

SubFilter::BalckWhite::BalckWhite():Base::Filter(this)
{

}

QColor SubFilter::BalckWhite::getColor(const QColor oldColor)
{
    const quint32 N{3};
    const qreal oldRgb[3][1]{{oldColor.redF()},{oldColor.greenF()},{oldColor.blueF()}};
    qreal newRgb[N];

    const qreal matrix[N][N]{{0.33, 0.33, 0.33},
                             {0.33, 0.33, 0.33},
                             {0.33, 0.33, 0.33}};

    for(quint32 i = 0; i < N; ++i)
    {
        for(quint32 j = 0; j < N; ++j)
        {
            newRgb[i] += matrix[i][j] * oldRgb[i][j];
            newRgb[i] = qBound(0.0, newRgb[i], 1.0);
        }
    }

    QColor newColor;
    newColor.setRgbF(newRgb[0], newRgb[1], newRgb[2]);
    return newColor;
}
