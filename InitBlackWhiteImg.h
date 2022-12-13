#ifndef INITBLACKWHITE_H
#define INITBLACKWHITE_H

#include "InitializeImg.h"

namespace Fk::Init
{
    class BlackWhite: public Fk::Base::InitializeImg
    {
        public:
            BlackWhite(const QString nameFileImg);
        private:
            void initialize();
    };
}

#endif // INITLACKWHITE_H
