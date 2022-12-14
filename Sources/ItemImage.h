#ifndef ITEMIMAGE_H
#define ITEMIMAGE_H

#include "Items.h"
#include "WgtImgProperty.h"
#include "WgtFilter.h"
#include "WgtFraming.h"

namespace Fk{
    class Image;
}

namespace App{
    class MainWindow;
}

namespace App::Item
{
    class Image: public App::Base::Item
    {
        Q_OBJECT

        public:
            explicit Image(App::MainWindow* const mainWin);
            QMenu* getMenu() const;
            Fk::Image getImage() const;
            void saveModifiedImage(QWidget* const widget);
        private:
            void updateFile(Fk::Image image) override final;
            void checkStatyActions() override final;
            void setFile(Fk::Image image) override final;
        private:
            void connectWithCommand();
            void initializeEachAction();
            void setPropertActions(bool value);
        private slots:
            void changeDepth();
            void showProperty();
            void changeFilters();
            void changeFrame();
        private:
            Fk::Image modifiedImage;
            std::unique_ptr<WinFrames> winFrames;
            std::unique_ptr<WinFilter> winFilter;
            std::unique_ptr<WinImgProperty> winProperty;
            QList<Fk::Image> images;
            std::unique_ptr<QAction> aDepth;
            std::unique_ptr<QAction> aProperty;
            std::unique_ptr<QAction> aFilter;
            std::unique_ptr<QAction> aFrame;
            std::unique_ptr<QMenu> mImage;
            App::MainWindow* const mainWindow;
    };
}
#endif // IMAGE_H
