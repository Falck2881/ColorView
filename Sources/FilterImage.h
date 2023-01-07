#ifndef FILTERIMAGE_H
#define FILTERIMAGE_H

#include <memory>
#include "CaluclateColor.h"
#include "Image.h"

class FilterImage
{
    public:
        FilterImage(FilterImage& oldObj);
        FilterImage(FilterImage&& oldObj);
        FilterImage(std::shared_ptr<Base::CalculateColor> newMethod);
        void applyFilter(Fk::Image* const image);
    private:
        std::shared_ptr<Base::CalculateColor> method;
};




#endif // FILTERIMAGE_H
