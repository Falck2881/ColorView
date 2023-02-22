#ifndef ITEMPAGE_H
#define ITEMPAGE_H

#include "Items.h"
#include <QTabWidget>
#include <QList>
#include <QLabel>

namespace App{
    class MainWindow;
}

namespace Fk{
    class Image;
}

namespace  App::Item
{
    class Page: public App::Base::Item
    {
        Q_OBJECT

        public:
           explicit Page(App::MainWindow* const mainWin);
           QTabWidget* getTabWidget() const;
           std::shared_ptr<Fk::Image> getImageCurrentPage() const;
           void updatePage(const Fk::Image& image);
           void hideStartPage();
           void setImageIntoPage(QWidget* const billboard, const Fk::Image& image);
        private:
           void connectWithCommand();
           void initializeStartPage();
        private slots:
           void currentPage(const qint32 index);
        private:
           std::unique_ptr<QTabWidget> tabWidget;
           App::MainWindow* const mainWindow;
           qint32 indexOnPage;
    };
}
#endif // ITEMPAGE_H
