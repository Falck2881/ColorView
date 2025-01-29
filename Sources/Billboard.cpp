#include "Billboard.h"
#include <QMouseEvent>
#include <QPainter>
#include <QImage>
#include <QVBoxLayout>

Fk::Billboard::Billboard(const Fk::Image& newImage):
    image(newImage),moveDraw(0.0,0.0),mouseTracking(false)
{
    pencilBox.readiness = Readiness::Show;
    if(image.getType() == Fk::TypeImage::SimpleImage)
        setPixmap(image.pixmap());

    setMaximumSize(image.width(), image.height());
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
    // Если просмотр то ничего не делаем
    if (pencilBox.readiness == Readiness::Show)
        return;

    if (pencilBox.readiness == Readiness::Zoom)
    {
        if (event->button() == Qt::MouseButton::LeftButton)
        {
            image.scaled(image.width() * 2, image.height() * 2);
            setPixmap(QPixmap::fromImage(image.context()));
        }

        if (event->button() == Qt::MouseButton::RightButton)
        {
            image.scaled(image.width() / 2, image.height() / 2);
            setPixmap(QPixmap::fromImage(image.context()));
        }

        emit updateBillboard(image);
        return;
    }

    // Если режим "Рисование" или "Редактирования" то отслеживаем перемещение мышки и её позицию для рисования
    if (pencilBox.readiness == Readiness::Drawing || pencilBox.readiness == Readiness::Edit)
    {
        mouseTracking = true;
        moveDraw = event->pos();
    }

    if (event->button() == Qt::MouseButton::LeftButton)
        pencilBox.color = colorToDrawing;

    if (event->button() == Qt::MouseButton::RightButton)
    {
        setCursor(QCursor(QPixmap(":/Normal/eraser.png")));
        colorToDrawing = pencilBox.color;
        pencilBox.color = QColor(255,255,255);
    }

}

void Fk::Billboard::mouseMoveEvent(QMouseEvent* event)
{
    if (pencilBox.readiness == Readiness::Show)
        return;

    if (mouseTracking)
    {
        moveDraw = event->pos();
        update();
    }

    QLabel::mouseMoveEvent(event);
}

void Fk::Billboard::paintEvent(QPaintEvent* event)
{
    Q_UNUSED(event);

    QImage context = image.context();

    if (!pixmap().isNull())
    {
        context = image.pixmap().toImage();
        context = context.scaled(event->rect().width(), event->rect().height());
    }

    QPainter painter;
    painter.begin(&context);
    painter.setPen(QPen(QBrush(pencilBox.color, Qt::BrushStyle::SolidPattern),pencilBox.width));
    painter.drawPoint(moveDraw.x() - 18.0f, moveDraw.y() + 18.0f);
    painter.end();

    setPixmap(QPixmap::fromImage(context));
    image.updateContext(context);
    QLabel::paintEvent(event);
}

int Fk::Billboard::width() const
{
    return image.width();
}

int Fk::Billboard::height() const
{
    return image.height();
}
