#ifndef ITEMS_H
#define ITEMS_H

#include <QObject>
#include <QAction>
#include <QToolBar>
#include <QToolButton>
#include <QMenu>
#include <memory>
#include "Content.h"
#include "Billboard.h"

namespace App::Base
{
    class Item: public QObject
    {
        Q_OBJECT

        public:
            Item() = default;
            virtual ~Item() = default;
            void setContent(const std::pair<QString,QString>& content);
            void updateContent(std::shared_ptr<Billboard> billboard);
            void setIndex(const qint32 newIndex);
            virtual void checkStatyActions(){};
        protected:
            Item(std::shared_ptr<Content> content);
            std::shared_ptr<Content> content;
    };
}
#endif // ITEMS_H
