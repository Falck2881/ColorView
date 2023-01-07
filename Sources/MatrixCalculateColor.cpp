#include "MatrixCalculateColor.h"
#include <QFile>
#include <QStringList>
#include <QRegularExpression>
#include <QRegularExpressionMatch>

MatrixCalculateColor::MatrixCalculateColor(MatrixCalculateColor& oldMethod)
{
    for(int i = 0; i < 3; ++i)
        for(int j = 0; j < 3; ++j)
            this->matrix[i][j] = oldMethod.matrix[i][j];
}

MatrixCalculateColor::MatrixCalculateColor(const QString nameFileMatrix)
{

    setMatrixFilter(nameFileMatrix);
}

void MatrixCalculateColor::highlightsMemoryForMatrix()
{

}

void MatrixCalculateColor::setMatrixFilter(const QString nameFileMatrix)
{
    QStringList valueMatrix = loadMatrix(nameFileMatrix);
    setValuesInMatrix(valueMatrix);
}

QStringList MatrixCalculateColor::loadMatrix(const QString nameFileMatrix)
{
    QStringList valueMatrix;
    QFile fileMatrix(nameFileMatrix);
    if(fileMatrix.open(QIODevice::ReadOnly))
    {
        QString symbols(fileMatrix.readAll());
        fileMatrix.close();
        QString endStr("(\r\n|\n)");
        QString pattern("(\\d\\.\\d\\d|\\d\\.\\d|\\d|-\\d)");
        QRegularExpression reg(pattern + "\\s{1,20}" + pattern + "\\s{1,20}" + pattern + endStr +
                               pattern + "\\s{1,20}" + pattern + "\\s{1,20}" + pattern + endStr +
                               pattern + "\\s{1,20}" + pattern + "\\s{1,20}" + pattern + endStr);

        QRegularExpressionMatch regMatch = reg.match(symbols);

        if(regMatch.hasMatch())
            valueMatrix = regMatch.capturedTexts();
    }

    return valueMatrix;
}

void MatrixCalculateColor::setValuesInMatrix(const QStringList &valuesMatrix)
{
    auto value{valuesMatrix.begin()+1};
    const quint32 N{3};

    for(quint32 i = 0; i < N; ++i, ++value)
    {
        for(quint32 j = 0; j < N && value < valuesMatrix.end(); ++j, ++value)
        {
            bool boolean(false);
            double vertex = value->toDouble(&boolean);
            if(boolean)
                matrix[i][j] = vertex;
        }
    }
}

QColor MatrixCalculateColor::calculateColor(QColor oldColor)
{
    const quint32 N{3};
    const qreal oldRgb[3][1]{{oldColor.redF()},{oldColor.greenF()},{oldColor.blueF()}};
    qreal newRgb[N]{0,0,0};


    for(quint32 i = 0; i < N; ++i)
    {
        for(quint32 j = 0; j < N; ++j)
        {
            newRgb[i] += matrix[i][j] * oldRgb[i][j];
            newRgb[i] = qBound(0.0,newRgb[i],1.0);
        }
    }

    QColor newColor;
    newColor.setRgbF(newRgb[0], newRgb[1], newRgb[2]);
    return newColor;
}

MatrixCalculateColor::~MatrixCalculateColor()
{

}
