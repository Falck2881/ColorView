#ifndef METHODPROCESSING_H
#define METHODPROCESSING_H

#include "Image.h"
#include <QVariant>

class MethodProcessing
{
    public:
        virtual ~MethodProcessing() = default;
        virtual QVariant processing(const Fk::Image& sourcesImage) = 0;
    protected:
        MethodProcessing() = default;
};

#endif // METHODPROCESSING_H
