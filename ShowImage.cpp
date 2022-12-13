#include "ShowImage.h"
#include "widget.h"
#include "Image.h"

Fk::Command::ShowImage::ShowImage
    (
        Widget* const mainWidget,
        std::shared_ptr<Fk::Base::InitializeImg> newInit
    ):
    mainWgd(mainWidget),
    currInitImg{std::move(newInit)}
{

}

void Fk::Command::ShowImage::execute()
{
    Fk::Image image(currInitImg);

    if(mainWgd != nullptr)
        mainWgd->setPropertyImage(image);
}
