#ifndef ITEMPENCILBOX_H
#define ITEMPENCILBOX_H

#include <memory>
#include <QObject>
#include <QToolBar>
#include <QAction>
#include "PencilBox.h"
#include "WgtSelectWidthPencil.h"

namespace App {
    class MainWindow;
}

 namespace App::Item
{
    class DrawingTools: public QObject
    {
        Q_OBJECT

        public:
            DrawingTools();
            QToolBar* getToolBar() const;
            const Fk::PencilBox& getPencilBox() const;
            void setActivateToolsDrawing(bool status);
        private:
            void initializeEachAction();
            void connectWithCommand();
        private slots:
            void setCursor();
            void setPencil();
            void setEraser();
            void setColor();
            void setWidthPencilAndEraser(qint32 width);
        signals:
            void toolsHaveBeenUpdate();
        private:
            std::unique_ptr<QToolBar> toolBar;
            std::unique_ptr<QAction> aCursor;
            std::unique_ptr<QAction> aPencilAndEraser;
            std::unique_ptr<QAction> aEraser;
            std::unique_ptr<QAction> aPalette;
            std::unique_ptr<QAction> aPenWidth;
            std::unique_ptr<WgtSelectWidthPencil> selectionWidget;
            Fk::PencilBox pencilBox;
            QColor colorToDrawing;
    };
}
#endif // ITEMPENCILBOX_H
