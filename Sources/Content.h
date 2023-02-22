#ifndef CONTENT_H
#define CONTENT_H

#include <utility>
#include <memory>
#include <QList>
#include <QtGlobal>
#include "ThreadProcessingImages.h"
#include "Image.h"
#include "Billboard.h"
#include "History.h"


class Content: public QObject
{
    Q_OBJECT

    public:
        virtual ~Content() = default;
        virtual void setContent(const std::pair<QString,QString>&){};
        virtual void updateContent(std::shared_ptr<Billboard>){};
        void setIndex(const qint32 index);
        bool isBillboardEmpty() const;
        qsizetype sizeBillboard() const;
        Fk::Image image() const;
        QVector<Fk::Image> images() const;
        auto historyAllBillboard() const;
        bool isHistoryEmpty() const;
        void undoModification();
        void redoModification();
        std::shared_ptr<Billboard> billboardInHistory() const;
        std::shared_ptr<Billboard> lastModifiedOnBillboard() const;
        void saveModifiedOnBillboard(std::shared_ptr<Billboard>);
        QVector<Fk::Image> collageOfImages() const;
    protected:
        void replaceBillboard(std::shared_ptr<Billboard> billboard);
        qint32 index;
        QVector<std::shared_ptr<Billboard>> billboards;
        QVector<Modified::Billboard::History<Billboard>> history;
        QVector<Fk::Image> collageProcessingBillboards;
        Content();
};

#endif // CONTENT_H
