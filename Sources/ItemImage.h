#ifndef ITEMIMAGE_H
#define ITEMIMAGE_H

#include "Items.h"
#include "WgtImgProperty.h"
#include "WgtFilter.h"
#include "WgtFraming.h"
#include "SetConversions.h"
#include "ThreadProcessingImages.h"

namespace Fk{
    class Image;
}

namespace App{
    class MainWindow;
}

namespace App
{
namespace Item {


    class Image: public App::Base::Item
    {
        Q_OBJECT

        public:
            explicit Image(App::MainWindow* const mainWin);
            QMenu* getMenu() const;
            Fk::Image getImage() const;
            void saveModifiedImage(QWidget* const widget);
            void updateActivityFilter();
            void updateContent(const Fk::Image& image) override final;
        private:
            void checkStatyActions() override final;
            void setContent(const Fk::Image& image) override final;
        private:
            void moveConversionsColorIntoThreads();
            void replaceImage(const Fk::Image& image);
            void startThreadProcessingImages(const Fk::Image& image);
            void connect();
            void initializeSubItemDepth();
            void initializeSubItemImage();
            void setPropertActions(bool value);
            bool isImageHightQuality(const Fk::Image& image) const;
            void addToCompleteImageProcessing(std::pair<QVector<Fk::Image>, NumbersThreads> newCompletedImageProcessing);
            void removeOldsProcessingImages();
        private slots:
            void setProcessingImages(std::pair<QVector<Fk::Image>, NumbersThreads> newCompletedImageProcessing);
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
            QVector<std::pair<QVector<Fk::Image>, NumbersThreads>> completedImageProcessing;
            SetConversions collection;
            QVector<std::shared_ptr<ThreadProcessingImages>> threadsProcessingImages;
            Fk::Image modifiedImage;
            QVector<Fk::Image> collectionSourceImages;
            QVector<Fk::Image> collectionProcessingImage;
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
