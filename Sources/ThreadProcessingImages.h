#ifndef THREADPROCESSINGIMAGE_H
#define THREADPROCESSINGIMAGE_H

#include <QVector>
#include <memory>
#include <QObject>
#include <QThread>
#include "MatrixFilter.h"
#include "Image.h"

class ThreadProcessingImages: public QObject
{
    Q_OBJECT

    public:
        ThreadProcessingImages(QVector<std::shared_ptr<ConversionColor>> methodsConversionColor);
        ~ThreadProcessingImages();
    public slots:
        void start();
        void applyProcessing(const Fk::Image& image);
    private:
        QVector<std::shared_ptr<ConversionColor>> methodsConversionColor;
        QThread thread;
    signals:
        void returnProcessingImages(QVector<Fk::Image> processingImages);
};

#endif // THREADPROCESSINGIMAGE_H
