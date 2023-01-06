#include "SCApplyFrame.h"
#include "Image.h"
#include "WgtFraming.h"

Command::ApplyFrame::ApplyFrame(const QString nameFileFrame, WinFrames* const winFrames):
    nameFileFrame(nameFileFrame),
    winFrames(winFrames)
{

}

void Command::ApplyFrame::setCurrentImage(Fk::Image currentImage)
{
    currentImg = currentImage;
}


void Command::ApplyFrame::execute()
{
    Fk::Image newImage = currentImg;
    newImage.setFraming(nameFileFrame);
    winFrames->setModifiedImage(newImage);
}
