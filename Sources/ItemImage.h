#ifndef ITEMIMAGE_H
#define ITEMIMAGE_H

#include "Items.h"
#include "WgtImgProperty.h"
#include "WgtFilter.h"
#include "WgtFraming.h"
#include "ContentItemImage.h"
#include <memory>

namespace App{
    class MainWindow;
}

namespace App
{
namespace Item
{
    class Image: public App::Base::Item
    {
        Q_OBJECT

        public:
            explicit Image(App::MainWindow* const mainWin);
            QMenu* getMenu() const;
            Fk::Image getImage() const;
            void saveModifiedImage(QWidget* const widget);
            void startThreads();
        private:
            void setActivityOfWidgets() override final;
            void setContent(const QString& content) override;
            void updateContent(const Fk::Image& image) override;
            void setIndex(const qint32 newIndex) override;
            void removeContent(const qint32 index) override;
        private:
            void connect();
            void initializeSubItemDepth();
            void initializeSubItemImage();
            void setActivityTheWidgetsWhichProcessingBillboard();
            void notifyMainWindow(const QString& message);
        private slots:
            void showProperty();
            void changeFilters();
            void changeFrame();
            void changeDepth256Color();
            void changeDepth16Color();
            void changeDepth24Color();
            void changeDepth32Color();
        signals:
            void sourceImage(const Fk::Image& image);
        private:
            std::shared_ptr<ContentItemImage> content;
            Fk::Image modifiedImage;
            std::unique_ptr<WinFrames> winFrames;
            std::unique_ptr<WinFilter> winFilter;
            std::unique_ptr<WinImgProperty> winProperty;
            std::unique_ptr<QMenu> mDepthColor;
            std::unique_ptr<QAction> aDepth256Color;
            std::unique_ptr<QAction> aDepth16Color;
            std::unique_ptr<QAction> aDepth24Color;
            std::unique_ptr<QAction> aDepth32Color;
            std::unique_ptr<QAction> aProperty;
            std::unique_ptr<QAction> aFilter;
            std::unique_ptr<QAction> aFrame;
            std::unique_ptr<QMenu> mImage;
            App::MainWindow* const mainWindow;
    };
}
}
#endif // IMAGE_H
