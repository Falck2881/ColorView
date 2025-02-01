#include "GraphicsImageItem.h"
#include "GraphicsBillboardScene.h"
#include <iostream>
#include <QMouseEvent>
#include <QPainter>
#include <QImage>
#include <QVBoxLayout>
#include <QGraphicsSceneMouseEvent>
#include <QWidget>
#include <QPixmap>

Fk::GraphicsImageItem::GraphicsImageItem(const Fk::Image& newImage):
    image(newImage),point(0.0,0.0)
{
    pencilBox.readiness = Readiness::Show;
    if(image.getType() == Fk::TypeImage::SimpleImage)
        setPixmap(image.pixmap());

    setCursor(QCursor(QPixmap(":/Normal/cursor.png")));
    setFlag(QGraphicsItem::ItemIsFocusable);
    setFlag(QGraphicsItem::ItemIsSelectable);

    setAcceptHoverEvents(true);
    setFocus();
}

void Fk::GraphicsImageItem::setPencilBox(Fk::PencilBox newPencilBox)
{
    pencilBox = newPencilBox;
    setCursor(pencilBox.cursor);
}

void Fk::GraphicsImageItem::setImage(const Fk::Image& newImage)
{
    image = newImage;
}


void Fk::GraphicsImageItem::zoomUp()
{
    image.scaled(image.width() * 2, image.height() * 2);
    setPixmap(QPixmap::fromImage(image.context()));
}

void Fk::GraphicsImageItem::zoomDown()
{
    image.scaled(image.width() / 2, image.height() / 2);
    setPixmap(QPixmap::fromImage(image.context()));
}

QRectF Fk::GraphicsImageItem::boundingRect() const
{
    return QRectF(0, 0, image.width(), image.height());
}

void Fk::GraphicsImageItem::paint(QPainter* pPainter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);
    Q_UNUSED(pPainter);

    QImage context = image.context();

    if (!pixmap().isNull())
        context = image.pixmap().toImage();

    QPainter imgPainter;
    imgPainter.begin(&context);
    imgPainter.setRenderHint(QPainter::Antialiasing);  // Включаем сглаживание, если нужно
    imgPainter.setPen(QPen(QBrush(pencilBox.color, Qt::BrushStyle::SolidPattern), pencilBox.width));

    // Рисуем точку (возможно, это как рисование на изображении)
    if (pencilBox.readiness == Readiness::Drawing)
        imgPainter.drawPoint(mapFromScene(point));

    imgPainter.end();

    setPixmap(QPixmap::fromImage(context));
    image.updateContext(context);
    QGraphicsPixmapItem::paint(pPainter, option, widget);
}

int Fk::GraphicsImageItem::width() const
{
    return image.width();
}

int Fk::GraphicsImageItem::height() const
{
    return image.height();
}

Fk::Image Fk::GraphicsImageItem::toImage() const
{
    return image;
}

void Fk::GraphicsImageItem::setMovePoint(QPointF newPoint)
{
    point = newPoint;
}
