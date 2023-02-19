#ifndef THREADPROCESSINGIMAGE_H
#define THREADPROCESSINGIMAGE_H

#include <utility>
#include <QVector>
#include <memory>
#include <QObject>
#include <QThread>
#include "MatrixFilter.h"
#include "Image.h"

enum class NumbersThreads{FIRST_THREAD, SECOND_THREAD, THIRD_THREAD};

class ThreadProcessingImages: public QThread
{
    Q_OBJECT

    public:
        ThreadProcessingImages();
        ~ThreadProcessingImages();
        void setMethodsConversionColor(QVector<std::shared_ptr<ConversionColor>> methodsConversionColor);
        void setNumberThread(NumbersThreads numberThread);
        void setCopyImage(Fk::Image image);
        bool isRun() const;
    protected:
        void run() override;
    private:
        void removeCollectionProcessingImages();
    private:
        QVector<std::shared_ptr<ConversionColor>> methodsConversionColor;
        NumbersThreads currentNumberThread;
        QVector<Fk::Image> collageProcessingImages;
    signals:
        void returnProcessingImages(std::pair<QVector<Fk::Image>, NumbersThreads> processingImages);
};

#endif // THREADPROCESSINGIMAGE_H
