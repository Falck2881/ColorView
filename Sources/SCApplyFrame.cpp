#include "SCApplyFrame.h"
#include "Image.h"
#include "WgtFraming.h"

Command::ApplyFrame::ApplyFrame(const QString nameFileFrame, WinFrames* const winFrames):
    nameFileFrame(nameFileFrame),
    winFrames(winFrames)
{

}

void Command::ApplyFrame::setCurrentImage(const Fk::Image& currentImage)
{
    currentImg = currentImage;
}


void Command::ApplyFrame::execute()
{
    currentImg.setFraming(nameFileFrame);
    winFrames->setModifiedImage(currentImg);
}
