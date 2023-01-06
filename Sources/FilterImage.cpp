#include "FilterImage.h"
#include "CaluclateColor.h"
#include "Image.h"

FilterImage::FilterImage(FilterImage& oldObj)
{
    this->method = std::move(oldObj.method);
}

FilterImage::FilterImage(FilterImage&& oldObj)
{
    this->method = std::move(oldObj.method);
}

FilterImage::FilterImage(std::shared_ptr<Base::CalculateColor> newMethod):
    method(newMethod)
{
}

void FilterImage::applyFilter(Fk::Image* const wrapper)
{
    std::scoped_lock(wrapper->mutex);
    QRgb* oldRgb;

    for(qint32 y = 0; y < wrapper->qImage().height(); ++y){
        oldRgb = reinterpret_cast<QRgb*>(wrapper->qImage().scanLine(y));
        for(qint32 x = 0; x < wrapper->qImage().width(); ++x)
        {
            QColor newColor = method->calculateColor(QColor(oldRgb[x]));
            wrapper->qImage().setPixelColor(x,y,newColor);
        }
    }

}


