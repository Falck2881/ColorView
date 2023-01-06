#include "AveragingColor.h"

QColor AveragingColor::calculateColor(QColor oldColor)
{
    QColor newColor;
    qreal averaging = (oldColor.redF() + oldColor.greenF() + oldColor.blueF())/3;
    newColor.setRgbF(averaging,averaging,averaging);
    return newColor;
}
