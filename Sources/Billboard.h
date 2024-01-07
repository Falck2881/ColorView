#ifndef BILLBOARD_H
#define BILLBOARD_H

#include <QLabel>
#include <QPointF>
#include "PencilBox.h"
#include "Image.h"

namespace Fk
{
    class Billboard: public QLabel
    {
        Q_OBJECT
        public:
            explicit Billboard(const Fk::Image& newImage);
            void setPencilBox(Fk::PencilBox pencilBox);
            void setImage(const Fk::Image& newImage);
            void mouseMoveEvent(QMouseEvent* mouseEvent) override;
            void mouseReleaseEvent(QMouseEvent* mouseEvent) override;
            void mousePressEvent(QMouseEvent* mouseEvent) override;
            void paintEvent(QPaintEvent* event) override;
        signals:
            void updateBillboard(Fk::Image image);
        private:
            Fk::PencilBox pencilBox;
            QColor colorToDrawing;
            Fk::Image image;
            QPointF moveDraw;
            bool mouseTracking;
    };
}
#endif // BILLBOARD_H
