#ifndef GRAPHICSBILLBOARDSCENE_H
#define GRAPHICSBILLBOARDSCENE_H

#include <QGraphicsScene>
#include <QRectF>
#include <memory>
#include "Image.h"
#include "GraphicsImageItem.h"

namespace Fk
{
    class GraphicsBillboardScene: public QGraphicsScene
    {
        Q_OBJECT

        public:
            explicit GraphicsBillboardScene(QRectF rectF);
            void addBillboard(std::shared_ptr<Fk::GraphicsImageItem> billboard);
            std::shared_ptr<Fk::GraphicsImageItem> getBillboard() const;
            void setPencilBox(Fk::PencilBox newPencilBox);
        protected :
            void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
            void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
            void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
        signals:
            void updateBillboard(Fk::Image& image);
        private:
            std::shared_ptr<Fk::GraphicsImageItem> billboard;
            bool mouseTracking;
            Fk::PencilBox pencilBox;

    };
}
#endif // GRAPHICSBILLBOARDSCENE_H
