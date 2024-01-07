#include "ItemDrawingTools.h"
#include <QColorDialog>

App::Item::DrawingTools::DrawingTools():
    toolBar{std::make_unique<QToolBar>()},
    aCursor{std::make_unique<QAction>("&Cursor")},
    aPencilAndEraser{std::make_unique<QAction>("&Pancil and eraser")},
    aEraser{std::make_unique<QAction>("&Eraser")},
    aPalette{std::make_unique<QAction>("&Palette")},
    aPenWidth{std::make_unique<QAction>("&Pen width")},
    selectionWidget{std::make_unique<WgtSelectWidthPencil>(toolBar.get())}
{
    initializeEachAction();
    connectWithCommand();
}

void App::Item::DrawingTools::initializeEachAction()
{
    QList<QString> namesFiles{":/Normal/cursor.png",":/Normal/pencil-normal.png",
                              ":/Normal/eraser.png",":/Normal/palette-normal.png",":/Normal/shirina-normal.png"};

    QList<QAction*> actions{aCursor.get(),aPencilAndEraser.get(),aEraser.get(),aPalette.get(),aPenWidth.get()};

    for(int i=0; i < actions.size(); ++i)
    {
        actions[i]->setIcon(QIcon(namesFiles.at(i)));
        actions[i]->setEnabled(false);
        toolBar->addAction(actions[i]);
    }
}

void App::Item::DrawingTools::connectWithCommand()
{
    QObject::connect(aCursor.get(), &QAction::triggered, this, &App::Item::DrawingTools::setCursor);

    QObject::connect(aPencilAndEraser.get(), &QAction::triggered, this, &App::Item::DrawingTools::setPencil);

    QObject::connect(aEraser.get(), &QAction::triggered, this, &App::Item::DrawingTools::setEraser);

    QObject::connect(aPalette.get(), &QAction::triggered, this, &App::Item::DrawingTools::setColor);

    QObject::connect(aPenWidth.get(), &QAction::triggered, selectionWidget.get(), &WgtSelectWidthPencil::show);

    QObject::connect(selectionWidget.get(), &WgtSelectWidthPencil::updateWidthPencil,
                     this, &App::Item::DrawingTools::setWidthPencilAndEraser);
}

void App::Item::DrawingTools::setCursor()
{
    pencilBox.cursor = QCursor(QPixmap(":/Normal/cursor.png"));
    pencilBox.readiness = Fk::Readiness::Show;
    emit toolsHaveBeenUpdate();
}

void App::Item::DrawingTools::setPencil()
{
    pencilBox.cursor = QCursor(QPixmap(":/Normal/pencil-normal.png"));
    pencilBox.color = colorToDrawing;
    pencilBox.readiness = Fk::Readiness::Drawing;
    emit toolsHaveBeenUpdate();
}

void App::Item::DrawingTools::setEraser()
{
    pencilBox.cursor = QCursor(QPixmap(":/Normal/eraser.png"));
    pencilBox.color = QColor(255,255,255);
    pencilBox.readiness = Fk::Readiness::Edit;
    emit toolsHaveBeenUpdate();
}

void App::Item::DrawingTools::setColor()
{
    QColor newColor = QColorDialog::getColor(Qt::white, toolBar.get(), QString(), QColorDialog::DontUseNativeDialog);

    if(newColor.isValid())
    {
        colorToDrawing = newColor;
        pencilBox.color = newColor;
        pencilBox.cursor = QCursor(QPixmap(":/Normal/pencil-normal.png"));
        pencilBox.readiness = Fk::Readiness::Drawing;
        emit toolsHaveBeenUpdate();
    }
}

void App::Item::DrawingTools::setWidthPencilAndEraser(qint32 width)
{
    pencilBox.width = width;
    emit toolsHaveBeenUpdate();
}

QToolBar* App::Item::DrawingTools::getToolBar() const
{
    return toolBar.get();
}

const Fk::PencilBox& App::Item::DrawingTools::getPencilBox() const
{
    return pencilBox;
}

void App::Item::DrawingTools::setActivateToolsDrawing(bool status)
{
    QList<QAction*> actions{aCursor.get(),aPencilAndEraser.get(),aEraser.get(),aPalette.get(),aPenWidth.get()};

    for(int i=0; i < actions.size(); ++i)
        actions[i]->setEnabled(status);
}
