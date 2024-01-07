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
    class Item: public QWidget
    {
        Q_OBJECT

        public:
            virtual ~Item() = default;
            virtual void updateContent(const Fk::Image& image){};
            virtual void removeContent(const qint32 index){};
            virtual void setIndex(const qint32 newIndex) = 0;
            virtual void setActivityOfWidgets(){};
            virtual void setContent(const QString& content) = 0;
            QString messageAboutAction() const;
            void writeNoteAboutAction(const QString& message);
        private:
            QString note;
        protected:
            Item() = default;

    };
}
#endif // ITEMS_H
