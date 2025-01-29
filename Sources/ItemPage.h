#ifndef ITEMPAGE_H
#define ITEMPAGE_H

#include "Billboard.h"
#include "PencilBox.h"
#include "Content.h"
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
           explicit Page(App::MainWindow* const mainWin);
           QTabWidget* getTabWidget() const;
           Fk::Image getImageCurrentPage() const;
           void preparePageToDrawing(const Fk::PencilBox& pencilBox);
           qint32 currentIndexOfPage() const;
        private:
           void updateContent(const Fk::Image& image) override;
           void setContent(const Fk::Image& content) override;
           void setIndex(const qint32 newIndex) override;
           void removeContent(const qint32 index) override;
        private:
           void removeStartPage(const qint32 index = 0);
           void addImageIntoBillboardOfPage(const Fk::Image& image);
           void enableTabsClosable();
           void connectWithCommand();
           void connectToBillboard(Fk::Image image);
           void initializeStartPage();
           void finishTheJob();
           bool checkIndexOnPage() const;
           void notifyAllColleagues();
           void isThereAnyPage();
           void setConnectWithBillboard(Fk::Billboard* const billboard);
           void saveCurrentIndexOfPage();
        private slots:
           void switchPage();
           void closePage(const qint32 index);
           void receiveUpdatedImage(Fk::Image image);
        private:
           std::shared_ptr<Content> content;
           std::unique_ptr<QTabWidget> tabWidget;
           App::MainWindow* const mainWindow;
           qint32 indexOfPage;
    };
}
#endif // ITEMPAGE_H
