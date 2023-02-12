#ifndef APPLYFRAME_H
#define APPLYFRAME_H

#include "Command.h"
#include "Image.h"

class WinFrames;

namespace Command
{
    class ApplyFrame: public Base::Command
    {
        Q_OBJECT
        public:
            ApplyFrame(const QString nameFileFrame, WinFrames* const winFrames);
            void setCurrentImage(const Fk::Image& currentImage);
        public slots:
            void execute() override final;
        private:
            QString nameFileFrame;
            WinFrames* const winFrames;
            Fk::Image currentImg;
    };
}
#endif // APPLYFRAME_H
