#ifndef CONTENT_H
#define CONTENT_H

#include <utility>
#include <memory>
#include <QList>
#include <QtGlobal>
#include "ThreadProcessingImages.h"
#include "Image.h"
#include "Billboard.h"

class Content: public QObject
{
    Q_OBJECT

    public:
        Content():index(0){}
        virtual ~Content() = default;
        virtual void setContent(const std::pair<QString,QString>&);
        virtual void updateContent(std::shared_ptr<Billboard>);
        virtual void removeContent(const qint32 index);
        void setIndex(const qint32 index);
        bool isBillboardEmpty() const;
        qsizetype sizeBillboard() const;
        Fk::Image image() const;
        QVector<Fk::Image> images() const;
    protected:
        void replaceBillboard(std::shared_ptr<Billboard> billboard);
        qint32 index;
        QVector<std::shared_ptr<Billboard>> billboards;
};

#endif // CONTENT_H
