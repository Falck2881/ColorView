#ifndef PAGEGRAPHICSSCENE_H
#define PAGEGRAPHICSSCENE_H

#include <QGraphicsScene>

namespace Fk
{
    class PageGraphicsScene: public QGraphicsScene
    {
        public:
            PageGraphicsScene(){};
            void mouseMoveEvent(QGraphicsSceneMouseEvent* event);
            void mousePressEvent(QGraphicsSceneMouseEvent* event);
    };
}
#endif // PAGEGRAPHICSSCENE_H
