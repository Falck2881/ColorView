#include "SCApplyDepth.h"
#include "Windows/WgtSaveImg.h"

Command::ApplyDepth::ApplyDepth
(WinSaveImg* const winFilter,
 QRadioButton* const radioButton,
 QImage::Format depthColor):
    winFilter(winFilter),button(radioButton),depthColor(depthColor)
{

}

void Command::ApplyDepth::execute()
{
    if(button->isChecked())
        winFilter->updateDepthColorsInImage(depthColor);
}
