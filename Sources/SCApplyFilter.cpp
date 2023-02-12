#include "SCApplyFilter.h"
#include "WgtFilter.h"

using namespace std;
Fk::Image applyProcessing(const Fk::Image &sourcesImg, std::shared_ptr<ConversionColor> methodConversionColor);

Command::ApplyFilter::ApplyFilter
    (std::shared_ptr<ConversionColor> methodConversionColor,
     WinFilter* const window):
    methodConversionColor(methodConversionColor),
    win{window}
{
}

void Command::ApplyFilter::setCurrentImage(const Fk::Image& sourcesImage)
{
    sourcesImg = sourcesImage;
}

void Command::ApplyFilter::execute()
{
    auto modifiedImage = applyProcessing(sourcesImg, methodConversionColor);
    win->setModifiedImage(modifiedImage);
}

Fk::Image applyProcessing(const Fk::Image &sourcesImg, std::shared_ptr<ConversionColor> methodConversionColor)
{
    Fk::Image newImg = sourcesImg;


    for(qsizetype y = 0; y < sourcesImg.height(); ++y){
        QRgb* rgb = reinterpret_cast<QRgb*>(const_cast<uchar*>(sourcesImg.scanLine(y)));
        for(qsizetype x = 0; x < sourcesImg.width(); ++x)
        {
            QColor newColor{methodConversionColor->conversion(QColor(rgb[x]))};
            newImg.setPixelColor(x,y,newColor);
        }
    }

    return newImg;
}
