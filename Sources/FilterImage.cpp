#include "FilterImage.h"
#include "CaluclateColor.h"
#include "Image.h"

FilterImage::FilterImage(FilterImage& oldObj)
{
    this->method = oldObj.method;
}

FilterImage::FilterImage(FilterImage&& oldObj)
{
    this->method = oldObj.method;
}

FilterImage::FilterImage(std::shared_ptr<Base::CalculateColor> newMethod):
    method(newMethod)
{
}

void FilterImage::applyFilter(Fk::Image* const wrapper)
{

    for(qint32 x = 0; x < wrapper->qImage().width(); ++x){
        for(qint32 y = 0; y < wrapper->qImage().height(); ++y)
        {
            QColor oldPixel(wrapper->qImage().pixelColor(x,y));
            QColor newColor = method->calculateColor(oldPixel);
            wrapper->qImage().setPixelColor(x,y,newColor);
        }
    }

}


