#ifndef GRAPHICSIMAGEITEM_H
#define GRAPHICSIMAGEITEM_H

#include <QGraphicsPathItem>
#include <QPointF>
#include <QRectF>
#include "PencilBox.h"
#include "Image.h"

namespace Fk
{
    class GraphicsImageItem: public QGraphicsPixmapItem
    {
        public:
            explicit GraphicsImageItem(const Fk::Image& newImage);
            virtual ~GraphicsImageItem(){}
            void setPencilBox(Fk::PencilBox pencilBox);
            void setImage(const Fk::Image& newImage);
            QRectF boundingRect() const override;
            void zoomUp();
            void zoomDown();
            void setMovePoint(QPointF point);
            void paint(QPainter* pPainter, const QStyleOptionGraphicsItem* option, QWidget* widget) override;
            int width() const;
            int height() const;
            Fk::Image toImage() const;
        private:
            Fk::PencilBox pencilBox;
            Fk::Image image;
            QPointF point;
    };
}
#endif // GRAPHICSIMAGEITEM_H
