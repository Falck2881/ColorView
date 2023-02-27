#ifndef ITEMPAGE_H
#define ITEMPAGE_H

#include "ContentItemPage.h"
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
           void removeStartPage(const qint32 index = 0);
           void addBillboardIntoPage(QWidget* const billboard, const Fk::Image& image);
           void enableTabsClosable();
        private:
           void setContent(const std::pair<QString, QString> &content) override;
           void updateContent(std::shared_ptr<Billboard> billboard) override;
           void setIndex(const qint32 newIndex) override;
           void removeContent(const qint32 index) override;
        private:
           void connectWithCommand();
           void initializeStartPage();
           void finishTheJob();
           bool checkIndexOnPage() const;
           void notifyAllColleagues();
           void isThereAnyPage();
        private slots:
           void switchPage();
           void closePage(const qint32 index);
        private:
           std::shared_ptr<ContentItemPage> content;
           std::unique_ptr<QTabWidget> tabWidget;
           App::MainWindow* const mainWindow;
    };
}
#endif // ITEMPAGE_H
