#ifndef CONTENTITEMEDIT_H
#define CONTENTITEMEDIT_H

#include "Content.h"
#include "History.h"

class ContentItemEdit
{
    public:
        ContentItemEdit():index(0){};
        Modified::Billboard::History<Billboard> atHistory(const qint32 index) const;
        void setIndex(const qint32 index);
        bool isHistoryEmpty() const;
        void undoModification();
        void redoModification();
        std::shared_ptr<Billboard> billboardInHistory() const;
        std::shared_ptr<Billboard> lastModifiedOnBillboard() const;
        void saveModifiedOnBillboard(std::shared_ptr<Billboard>);
        void setContent(const std::pair<QString,QString>& newContent);
        void removeContent(const qint32 index);
    private:
        QVector<Modified::Billboard::History<Billboard>> history;
        qint32 index;
};

#endif // CONTENTITEMEDIT_H
