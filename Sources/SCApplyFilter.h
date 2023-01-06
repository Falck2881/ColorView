#ifndef SCAPPLYFILTER_H
#define SCAPPLYFILTER_H

#include "Command.h"
#include "FilterImage.h"
#include "CaluclateColor.h"
#include <memory>

class WinFilter;

namespace Command
{
    class ApplyFilter: public Base::Command
    {
        Q_OBJECT

        public:
            ApplyFilter(std::shared_ptr<FilterImage> filter,WinFilter* const window);
            void setCurrentImage(Fk::Image currentImage);

        public slots:
            void execute() override final;
        private:
            std::shared_ptr<FilterImage> filter;
            WinFilter* const win;
            Fk::Image currentImg;
    };
}

#endif // SCAPPLYFILTER_H
