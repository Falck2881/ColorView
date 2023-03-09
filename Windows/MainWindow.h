#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <memory>
#include <QList>
#include <QMovie>
#include <QLabel>
#include <QSplitter>
#include "ItemFile.h"
#include "ItemEdit.h"
#include "ItemPage.h"
#include "ItemImage.h"
#include "Billboard.h"

namespace Fk{
    class Image;
}

namespace App
{

    class MainWindow : public QMainWindow
    {
        Q_OBJECT

        public:
            MainWindow();
            void appand(App::Base::Item* const observer);
            void setBillboardInEachObserver(const QString& newContent);
            void changeIndex(const qint32 newIndex);
            void updateBillboardInEachObserver(std::shared_ptr<Billboard> billboard);
            void changeContentOfItems(Base::Item* const item);
            void notifyAboutClosePage(const qint32 index);
            void setActivityTheWitgetsInEachObserver();
            void closePage(const qint32 index);
            void closePageWithoutSave();
            void closePageAndSave();
            bool observersExist() const;
            void updateMessageInStatusBar(App::Base::Item* const item);
        private:
            void initializeMembersOfClass();
            void addAllItemsInManinWindow();
            void setGeometryScreen();
        private:
            std::unique_ptr<App::Item::File> itemFile;
            std::unique_ptr<App::Item::Edit> itemEdit;
            std::unique_ptr<App::Item::Image> itemImage;
            std::unique_ptr<App::Item::Page> itemPage;
            QList<App::Base::Item*> observers;
    };

}

#endif // MAINWINDOW_H
