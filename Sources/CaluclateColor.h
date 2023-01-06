#ifndef CALUCLATECOLOR_H
#define CALUCLATECOLOR_H

#include <QColor>

namespace Base
{
    class CalculateColor
    {
        public:
            virtual ~CalculateColor() = default;
            virtual QColor calculateColor(QColor oldColor) = 0;
        protected:
            CalculateColor() = default;
    };

}

#endif // CALUCLATECOLOR_H
