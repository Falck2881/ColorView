#ifndef ITEMS_H
#define ITEMS_H

#include <QObject>
#include <QAction>
#include <QToolBar>
#include <QToolButton>
#include <QMenu>
#include <memory>
#include "Image.h"

namespace App::Base
{
    class Item: public QObject
    {
        Q_OBJECT

        public:
            virtual ~Item() = default;
            virtual void updateContent(const Fk::Image&){}
            virtual void setContent(const Fk::Image&){}
            virtual void checkStatyActions(){};
            void saveIndex(const qint32 newIndex)
            {
                indexOnFile = newIndex;
            };
        protected:
            qsizetype indexOnFile;
            Item() = default;
    };
}
#endif // ITEMS_H
