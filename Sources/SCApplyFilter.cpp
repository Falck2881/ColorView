#include "SCApplyFilter.h"
#include "WgtFilter.h"

Command::ApplyFilter::ApplyFilter(std::shared_ptr<FilterImage> filter, WinFilter* const window):
    filter(filter),
    win{window}
{

}

void Command::ApplyFilter::setCurrentImage(Fk::Image currentImage)
{
    currentImg = currentImage;
}

void Command::ApplyFilter::execute()
{
    Fk::Image image = currentImg;
    image.setFilter(filter);
    win->setModifiedImage(image);
}
