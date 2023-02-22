#ifndef ITEMFILE_H
#define ITEMFILE_H

#include "Windows/WgtSaveImg.h"
#include "Items.h"
#include "Image.h"
#include <QDebug>
#include "Content.h"

namespace App{
    class MainWindow;
}

namespace App::Item
{
    class File: public App::Base::Item
    {
        Q_OBJECT

        public:
            explicit File(App::MainWindow* const mainWin);
            QMenu* getMenu() const;
            QToolBar* getToolBar() const;

        private:
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
            void exit();

        private:

            std::unique_ptr<QAction> aExite;
            std::unique_ptr<QAction> aSaveFileAs;
            std::unique_ptr<QAction> aSaveFile;
            std::unique_ptr<QAction> aOpenFile;
            std::unique_ptr<QMenu> mFile;
            std::unique_ptr<QToolBar> toolBar;
            App::MainWindow* const mainWindow;
            std::unique_ptr<WinSaveImg> winSaveImg;

    };
}
#endif // ITEMFILE_H
