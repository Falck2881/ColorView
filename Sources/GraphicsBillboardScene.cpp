#include "GraphicsBillboardScene.h"
#include <QGraphicsSceneMouseEvent>

Fk::GraphicsBillboardScene::GraphicsBillboardScene(QRectF rectF) :
    QGraphicsScene(rectF),
    mouseTracking(false)
{

}

void Fk::GraphicsBillboardScene::addBillboard(std::shared_ptr<Fk::GraphicsImageItem> newBillboard)
{
    billboard = newBillboard;
    addItem(billboard.get());
}

std::shared_ptr<Fk::GraphicsImageItem> Fk::GraphicsBillboardScene::getBillboard() const
{
    return billboard;
}

void Fk::GraphicsBillboardScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsScene::mouseReleaseEvent(event);

    if(pencilBox.readiness == Readiness::Show)
        return;

    if(pencilBox.readiness == Readiness::Drawing)
        billboard->setCursor(QCursor(QPixmap(":/Normal/pencil-normal.png")));

    mouseTracking = false;

    auto image = billboard->toImage();
    emit updateBillboard(image);
}


void Fk::GraphicsBillboardScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    // Если просмотр то ничего не делаем
    if (pencilBox.readiness == Readiness::Show)
        return;

    if (pencilBox.readiness == Readiness::Zoom)
    {
        if (event->button() == Qt::MouseButton::LeftButton)
            billboard->zoomUp();

        if (event->button() == Qt::MouseButton::RightButton)
            billboard->zoomDown();

        auto image = billboard->toImage();
        emit updateBillboard(image);

        return;
    }

    // Если режим "Рисование" или "Редактирования" то отслеживаем перемещение мышки и её позицию для рисования
    if (pencilBox.readiness == Readiness::Drawing || pencilBox.readiness == Readiness::Edit)
    {
        mouseTracking = true;
        billboard->setMovePoint(event->scenePos());
    }

    if (event->button() == Qt::MouseButton::RightButton)
    {
        billboard->setCursor(QCursor(QPixmap(":/Normal/eraser.png")));
        pencilBox.color = QColor(255,255,255);
        billboard->setPencilBox(pencilBox);
    }

}

void Fk::GraphicsBillboardScene::mouseMoveEvent(QGraphicsSceneMouseEvent* event)
{
    QGraphicsScene::mouseMoveEvent(event);

    if (pencilBox.readiness == Readiness::Show)
        return;

    if (mouseTracking){
        billboard->setMovePoint(event->scenePos());
    }
}

void Fk::GraphicsBillboardScene::setPencilBox(Fk::PencilBox newPencilBox)
{
    pencilBox = newPencilBox;
    billboard->setPencilBox(newPencilBox);
}
