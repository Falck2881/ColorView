#include "Billboard.h"
#include <QMouseEvent>
#include <QPainter>


Fk::Billboard::Billboard(const Fk::Image& newImage):
    image(newImage),moveDraw(0.0,0.0),mouseTracking(false)
{
    pencilBox.readiness = Readiness::Show;
    setPixmap(image.pixmap());
    setAlignment(Qt::AlignCenter);
    setCursor(QCursor(QPixmap(":/Normal/cursor.png")));
    setMouseTracking(true);
}

void Fk::Billboard::setPencilBox(Fk::PencilBox newPencilBox)
{
    pencilBox = newPencilBox;
    colorToDrawing = pencilBox.color;
    setCursor(pencilBox.cursor);
}

void Fk::Billboard::setImage(const Fk::Image& newImage)
{
    image = newImage;
}

void Fk::Billboard::mouseReleaseEvent(QMouseEvent* event)
{
    if(pencilBox.readiness == Readiness::Show)
        return;

    if(pencilBox.readiness == Readiness::Drawing)
        setCursor(QCursor(QPixmap(":/Normal/pencil-normal.png")));


    mouseTracking = false;
    QLabel::mouseReleaseEvent(event);
    emit updateBillboard(image);
}


void Fk::Billboard::mousePressEvent(QMouseEvent* event)
{
    if(pencilBox.readiness == Readiness::Show)
        return;

    if(pencilBox.readiness == Readiness::Drawing || pencilBox.readiness == Readiness::Edit)
    {
        mouseTracking = true;
        moveDraw = event->globalPosition();
    }

    if(event->button() == Qt::MouseButton::LeftButton)
        pencilBox.color = colorToDrawing;

    if(event->button() == Qt::MouseButton::RightButton)
    {
        setCursor(QCursor(QPixmap(":/Normal/eraser.png")));
        colorToDrawing = pencilBox.color;
        pencilBox.color = QColor(255,255,255);
    }

}

void Fk::Billboard::mouseMoveEvent(QMouseEvent* event)
{
    if(pencilBox.readiness == Readiness::Show)
        return;

    if(mouseTracking)
    {
        moveDraw = event->globalPosition();
        update();
    }

    QLabel::mouseMoveEvent(event);
}

void Fk::Billboard::paintEvent(QPaintEvent* event)
{
    Q_UNUSED(event);

    QImage context = image.context();
    QPainter painter;
    painter.begin(&context);
    painter.setPen(QPen(QBrush(pencilBox.color, Qt::BrushStyle::SolidPattern),pencilBox.width));
    if(image.getType() == Fk::TypeImage::DrawImage)
        painter.drawPoint(moveDraw.rx() + 120.0f, moveDraw.ry() + 25.0f);
    else
        painter.drawPoint(moveDraw.rx() -  412.0f, moveDraw.ry() - 182.0f);
    painter.end();

    setPixmap(image.pixmap());
    image.updateContext(context);
    QLabel::paintEvent(event);
}
