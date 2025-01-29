#ifndef CONTENT_H
#define CONTENT_H

#include <QObject>
#include <utility>
#include <memory>
#include <QList>
#include <QtGlobal>
#include "Image.h"

class Content: public QObject
{
    Q_OBJECT

    public:
        Content();
        virtual ~Content() = default;
        virtual void setContent(const Fk::Image&);
        virtual void updateContent(const Fk::Image&);
        virtual void removeContent(const qint32 index);
        void setIndex(const qint32 index);
        bool isBillboardEmpty() const;
        qsizetype sizeBillboard() const;
        const Fk::Image& image() const;
        const Fk::Image& lastImage() const;
        QVector<Fk::Image> images() const;
        void replaceImage(Fk::Image image);
    protected:
        qint32 index;
        QVector<Fk::Image> imageArray;
};

#endif // CONTENT_H
