#ifndef ITEMFILE_H
#define ITEMFILE_H

#include "Windows/WgtSaveImg.h"
#include "Items.h"
#include "Image.h"
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
        public slots:
            void save();
            void saveAs();
        private:
            void setActivityOfWidgets() override final;
            void setContent(const Fk::Image& content) override;
            void updateContent(const Fk::Image& billboard) override;
            void setIndex(const qint32 newIndex) override;
            void removeContent(const qint32 index) override;
        private:
            void connectWithCommand();
            void initializeDialogWindow();
            void initializeEachAction();
            void setPropertyActions(bool value, const QVector<QString>& icons);
            QString getPathToFile() const;
        signals:
            void openFile(const QString&);
            void createNewFileImage();
        private slots:
            void open();
            void exit();
            void add();
        private:
            std::shared_ptr<Content> content;
            std::unique_ptr<QAction> aExite;
            std::unique_ptr<QAction> aSaveFileAs;
            std::unique_ptr<QAction> aSaveFile;
            std::unique_ptr<QAction> aOpenFile;
            std::unique_ptr<QAction> aCreateImage;
            std::unique_ptr<QMenu> mFile;
            std::unique_ptr<QToolBar> toolBar;
            App::MainWindow* const mainWindow;
            std::unique_ptr<WinSaveImg> winSaveImg;
    };
}
#endif // ITEMFILE_H
