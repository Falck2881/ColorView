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
        private:
            void updateContant(Fk::Image image) override final;
            void checkStatyActions() override final;
            void setContant(Fk::Image image) override final;
        private:
            void replaceImage(const Fk::Image& image);
            void startThreadProcessingImages(const Fk::Image& image);
            void connectW();
            void initializeEachAction();
            void setPropertActions(bool value);
        private slots:
            void updateProcessingImages(QVector<Fk::Image> processingImages);
            void changeDepth();
            void showProperty();
            void changeFilters();
            void changeFrame();
        signals:
            void sourceImage(const Fk::Image& image);
        private:
            SetConversions collection;
            ThreadProcessingImages* threadProcessingImg;
            Fk::Image modifiedImage;
            QList<Fk::Image> collectionSourceImages;
            QVector<Fk::Image> collectionProcessingImage;
            std::unique_ptr<WinFrames> winFrames;
            std::unique_ptr<WinFilter> winFilter;
            std::unique_ptr<WinImgProperty> winProperty;
            std::unique_ptr<QAction> aDepth;
            std::unique_ptr<QAction> aProperty;
            std::unique_ptr<QAction> aFilter;
            std::unique_ptr<QAction> aFrame;
            std::unique_ptr<QMenu> mImage;
            App::MainWindow* const mainWindow;
    };
}
}
#endif // IMAGE_H
