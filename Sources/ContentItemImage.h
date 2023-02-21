#ifndef CONTENTITEMIMAGE_H
#define CONTENTITEMIMAGE_H

#include "Content.h"
#include "ThreadProcessingImages.h"
#include "SetConversions.h"
#include "ItemImage.h"

class ContentItemImage: public Content
{
    Q_OBJECT

    public:
        ContentItemImage();
        void setContent(const std::pair<QString,QString>& newContent) override;
        void updateContent(std::shared_ptr<Billboard> billboard) override;
        void startThreadsForProcessingImages(const Fk::Image& image);
    private:
        void moveConversionsColorIntoThreads();
        void connect();
        void addCompletedBillboardProcessing(std::pair<QVector<Fk::Image>, NumbersThreads> newCompletedBillboardProcessing);
        void removeOldsProcessingBillboards();
    private slots:
        void setProcessingBillboards(std::pair<QVector<Fk::Image>, NumbersThreads> newCompletedBillboardProcessing);
    private:
        SetConversions collection;
        QVector<std::shared_ptr<ThreadProcessingImages>> threadsProcessingImages;
        QVector<std::pair<QVector<Fk::Image>, NumbersThreads>> readyProcessingOfBillboard;

};

#endif // CONTENTITEMIMAGE_H
