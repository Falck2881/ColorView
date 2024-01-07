#ifndef CONTENTITEMIMAGE_H
#define CONTENTITEMIMAGE_H

#include "Content.h"
#include "ThreadProcessingImages.h"
#include "SetConversions.h"

class ContentItemImage: public Content
{
    Q_OBJECT

    public:
        ContentItemImage();
        void updateContent(const Fk::Image& billboard) override;
        void startThreads(const Fk::Image& image);
        QVector<Fk::Image> collageOfImages() const;
    private:
        void moveConversionsColorIntoThreads();
        void connect();
        void addCompletedImageProcessing(std::pair<QVector<Fk::Image>, NumbersThreads> newCompletedImageProcessing);
        void removeOldsProcessingImage();
    private slots:
        void setProcessingImage(std::pair<QVector<Fk::Image>, NumbersThreads> newCompletedImageProcessing);
    private:
        SetConversions collection;
        QVector<std::shared_ptr<ThreadProcessingImages>> threadsProcessingImages;
        QVector<std::pair<QVector<Fk::Image>, NumbersThreads>> readyProcessingOfImages;
        QVector<Fk::Image> collageProcessingImages;
};

#endif // CONTENTITEMIMAGE_H
