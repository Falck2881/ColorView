#ifndef SCAPPLYDEPTH_H
#define SCAPPLYDEPTH_H

#include "Command.h"
#include <QRadioButton>
#include <QImage>

class WinSaveImg;

namespace Command
{
    class ApplyDepth: public Base::Command
    {
        Q_OBJECT
        public:
            ApplyDepth(WinSaveImg* const wiFilter,
                       QRadioButton* const button,
                       QImage::Format depthColor);
            void execute() override final;
        private:
            WinSaveImg* const winFilter;
            QRadioButton* const button;
            QImage::Format depthColor;
    };
}
#endif // SCAPPLYDEPTH_H
