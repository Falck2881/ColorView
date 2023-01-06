#ifndef ITEMPAGE_H
#define ITEMPAGE_H

#include "Items.h"
#include <QTabWidget>
#include <QList>

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
           Page(App::MainWindow* const mainWin);
           QTabWidget* getTabWidget() const;
        private:
           void updateContant(Fk::Image image) override final;
           void setContant(Fk::Image image) override final;
        private:
           void connectWithCommand();
           void initializeStartPage();
           void hideStartPage();
        private slots:
           void currentPage(const qint32 index);
        private:
           QList<Fk::Image> images;
           std::unique_ptr<QTabWidget> tabWidget;
           App::MainWindow* const mainWindow;
    };
}
#endif // ITEMPAGE_H
