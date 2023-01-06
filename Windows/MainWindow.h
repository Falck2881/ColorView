#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <memory>
#include <QList>
#include "ItemFile.h"
#include "ItemEdit.h"
#include "ItemPage.h"
#include "ItemImage.h"

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
            void setFileInEachObserver(Fk::Image image);
            void changeIndexOnFile(const quint32 index);
            void updateFileInEachObserver(Fk::Image image);
            void changesItems(Base::Item* const item);
        private:
            void initializeItemsApp();
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
