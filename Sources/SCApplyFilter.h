#ifndef SCAPPLYFILTER_H
#define SCAPPLYFILTER_H

#include "Command.h"
#include "ConversionColor.h"
#include "Image.h"
#include <memory>

class WinFilter;

namespace Command
{
    class ApplyFilter: public Base::Command
    {
        Q_OBJECT

        public:
            ApplyFilter(std::shared_ptr<ConversionColor> methodConversionColor,
                        WinFilter* const window);
            void setCurrentImage(const Fk::Image& sourcesImage);
        private:
           void connect();
        public slots:
            void execute() override final;
        private:
            std::shared_ptr<ConversionColor> methodConversionColor;
            WinFilter* const win;
            Fk::Image sourcesImg;
    };
}

#endif // SCAPPLYFILTER_H
