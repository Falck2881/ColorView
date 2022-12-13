#ifndef SHOWIMAGE_H
#define SHOWIMAGE_H

#include "Command.h"
#include "InitializeImg.h"

class Widget;

namespace Fk::Command {

    class ShowImage: public Fk::Base::Command
    {
        Q_OBJECT

        public:
            ShowImage(Widget* const mainWidget,
                      std::shared_ptr<Fk::Base::InitializeImg> newInit);
        private slots:
            void execute() override final;
        private:
            Widget* mainWgd;
            std::shared_ptr<Fk::Base::InitializeImg> currInitImg;
    };
}
#endif // SHOWIMAGE_H
