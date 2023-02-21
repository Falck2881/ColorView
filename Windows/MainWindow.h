#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <memory>
#include <QList>
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
            void setBillboardInEachObserver(const std::pair<QString,QString>& content);
            void changeIndexOnFile(const quint32 index);
            void updateBillboardInEachObserver(std::shared_ptr<Billboard> billboard);
            void changesItems(Base::Item* const item);
            bool observersExist() const;
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
