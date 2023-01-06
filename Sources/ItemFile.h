#ifndef ITEMFILE_H
#define ITEMFILE_H

#include "Items.h"
#include "Image.h"
#include <QDebug>

namespace App{
    class MainWindow;
}

namespace App::Item
{
    class File: public App::Base::Item
    {
        Q_OBJECT

        public:
            File(App::MainWindow* const mainWin);
            QMenu* getMenu() const;
            QToolBar* getToolBar() const;

        private:
            void updateContant(Fk::Image image) override final;
            void setContant(Fk::Image image) override final;
            void checkStatyActions() override final;

        private:
            void connectWithCommand();
            void initializeDialogWindow();
            void initializeEachAction();
            void setPropertyActions(bool value, const QVector<QString>& icons);

        private slots:
            void open();
            void save();
            void saveAs();
            void exportAs();
            void exit();

        private:
            std::unique_ptr<QAction> aExite;
            std::unique_ptr<QAction> aExportAs;
            std::unique_ptr<QAction> aSaveFileAs;
            std::unique_ptr<QAction> aSaveFile;
            std::unique_ptr<QAction> aOpenFile;
            std::unique_ptr<QMenu> mFile;
            QList<Fk::Image> images;
            std::unique_ptr<QToolBar> toolBar;
            App::MainWindow* const mainWindow;

    };
}
#endif // ITEMFILE_H
