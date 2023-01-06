#include "SetConversions.h"
#include "MatrixFilter.h"
#include <QFile>
#include <QTextStream>

SetConversions::SetConversions()
{
    loadMethodsConversion();
}

QVector<std::shared_ptr<ConversionColor>> SetConversions::getFilters() const
{
    return methodsConversionColor;
}

void SetConversions::loadMethodsConversion()
{
    auto dataMatrices = loadValue();
    auto iterDataMatrix{dataMatrices.begin()};

    for(qsizetype i = 0; i < dataMatrices.size(); ++i, ++iterDataMatrix)
    {
        // added methods of conversion "matrix of filters" is
        auto arraysValues{extractValue(iterDataMatrix)};
        methodsConversionColor.push_back(std::make_shared<Conversion::MatrixColor>(arraysValues));
    }

    //Added method of conversion "averaging color" for black&white of filter
    methodsConversionColor.insert(1,std::make_shared<Conversion::AveragingColor>());
}

QVector<QByteArray> SetConversions::loadValue()
{
    QVector<QByteArray> dataMatrixes;
    QVector<QString> nameMatrix{":/Forest.txt", ":/Pink.txt",
                                ":/Saturation.txt", ":/Warm.txt", ":/Cool.txt"};

    for(qsizetype i = 0; i < nameMatrix.size(); ++i)
    {
        QFile file(nameMatrix.at(i));
        if(file.open(QIODevice::ReadOnly))
            dataMatrixes.push_back(QByteArray(file.readAll()));
    }

    return dataMatrixes;
}


std::array<std::array<float,4>,4> SetConversions::extractValue(QVector<QByteArray>::iterator iterByteArr)
{
    std::array<std::array<float,4>,4> arraysValues;
    QTextStream data(*iterByteArr,QIODevice::ReadOnly);
    data.setRealNumberPrecision(3);
    data.setRealNumberNotation(QTextStream::FixedNotation);

    for(qsizetype i = 0; i < 4; ++i)
        for(qsizetype j = 0; j < 4; ++j)
            data >> arraysValues.at(i).at(j);


    return arraysValues;
}
