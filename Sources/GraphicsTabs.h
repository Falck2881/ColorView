#ifndef GRAPHICSTABS_H
#define GRAPHICSTABS_H

#include <QGraphicsScene>
#include "GraphicsImage.h"

namespace Fk
{
    class GraphicsTabs
    {
        public:
            GraphicsTabs();
            std::unique_ptr<Fk::Billboard> billboard;
            std::unique_ptr<QGraphicsScene> scene;
    };
}

#endif // GRAPHICSTABS_H
