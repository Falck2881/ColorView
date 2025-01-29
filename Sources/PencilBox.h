#ifndef PENCILBOX_H
#define PENCILBOX_H

#include <QPen>
#include <QBrush>
#include <QCursor>
#include <QColor>

namespace Fk
{
    enum class Readiness{Show, Edit, Drawing, Zoom};

    class PencilBox
    {
        public:
            PencilBox();
            QColor color;
            QCursor cursor;
            Readiness readiness;
            qint32 width;
    };
}
#endif // PENCILBOX_H
