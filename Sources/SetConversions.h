#ifndef SETCONVERSIONS_H
#define SETCONVERSIONS_H

#include <QVector>
#include <QByteArray>
#include <array>
#include "ConversionColor.h"
#include "Image.h"

class SetConversions
{
       public:
           SetConversions();
           QVector<std::shared_ptr<ConversionColor>> getFilters() const;
       private:
           void loadMethodsConversion();
           QVector<QByteArray> loadValue();
           std::array<std::array<float,4>,4>  extractValue(QVector<QByteArray>::iterator data);
       private:
           QVector<std::shared_ptr<ConversionColor>> methodsConversionColor;
};

#endif // SETCONVERSIONS_H
