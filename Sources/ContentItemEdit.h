#ifndef CONTENTITEMEDIT_H
#define CONTENTITEMEDIT_H

#include "History.h"

class ContentItemEdit
{
    public:
        ContentItemEdit():index(0){};
        Modified::Image::History<Fk::Image> atHistory(const qint32 index) const;
        void setIndex(const qint32 index);
        bool isHistoryEmpty() const;
        void undoModification();
        void redoModification();
        Fk::Image imageInHistory() const;
        Fk::Image lastModifiedOnImage() const;
        void saveModifiedOnImage(const Fk::Image&);
        void setContent(const QString& newContent);
        void removeContent(const qint32 index);
    private:
        QVector<Modified::Image::History<Fk::Image>> history;
        qint32 index;
};

#endif // CONTENTITEMEDIT_H
