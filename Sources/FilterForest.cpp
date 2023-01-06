#include "FilterForest.h"

namespace Matrix {
    int a = 2;
}

SubFilter::Forest::Forest():Base::Filter(this)
{

}

QColor SubFilter::Forest::getColor(const QColor oldColor)
{
    const quint32 N{3};
    qreal newRgb[N]{0,0,0};
    qreal oldRgb[N][1]{{oldColor.redF()},{oldColor.greenF()},{oldColor.blueF()}};

    qreal matrix[N][N] = {{1.0, 0.3, 0},
                          {0,  1.0 , 0},
                          {0, 0.3, 1.0}};


    for(quint32 i = 0; i < N; ++i){
        for(quint32 j = 0; j < N; ++j){
            newRgb[i] += matrix[i][j] * oldRgb[i][j];
            newRgb[i] = qBound(0.0, newRgb[i], 1.0);
        }
    }

    QColor newColor;
    newColor.setRgbF(newRgb[0],newRgb[1],newRgb[2]);
    return  newColor;
}
