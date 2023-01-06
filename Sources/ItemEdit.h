#ifndef ITEMEDIT_H
#define ITEMEDIT_H

#include "Items.h"
#include "History.h"

namespace App{
    class MainWindow;
}

namespace App::Item
{
    class Edit: public App::Base::Item
    {
        Q_OBJECT

        public:
            explicit Edit(App::MainWindow* const mainWin);
            QMenu* getMenu() const;
            virtual QToolBar* getToolBar() const;
            void saveChangesInHistory(Fk::Image image);
            Fk::Image getCurrentImage() const;
        private:
            void checkStatyActions() override final;
            void setContant(Fk::Image image) override final;
        private:
            void initializeEachAction();
            void connectWithCommand();
            void setPropertyActions(bool value, const QVector<QString>& icons);
        private slots:
            void undo();
            void redo();
        private:
            Fk::Image imageInHistory;
            QVector<FileModified::History<Fk::Image>> historyEdit;
            std::unique_ptr<QAction> aUndo;
            std::unique_ptr<QAction> aRedo;
            std::unique_ptr<QMenu> mEdit;
            std::unique_ptr<QToolBar> toolBar;
            App::MainWindow* const mainWindow;
    };
}
#endif // ITEMEDIT_H
