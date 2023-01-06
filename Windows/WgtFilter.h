#ifndef WGTFILTER_H
#define WGTFILTER_H

#include <QWidget>
#include "SCApplyFilter.h"
#include "Image.h"
#include "SetConversions.h"

namespace App::Item {
    class Image;
}

namespace Ui {
class Filter;
}

class WinFilter : public QWidget
{
    Q_OBJECT

    public:
        explicit WinFilter(App::Item::Image* const imageItem);
        ~WinFilter();
        Fk::Image getModifiedImage() const;
        void updateContant(const Fk::Image image,
                           const QVector<Fk::Image> imagesAfterProcessing);
        void setModifiedImage(Fk::Image modifiedImage);
    private:
        void initializeCommands();
        void connect();
        void updateContainFrames(QVector<Fk::Image> images);
        void updateMainFrame(Fk::Image image);
        void updateCommands(Fk::Image image);
    private slots:
        void apply();
    private:
        Ui::Filter *ui;
        SetConversions collection;
        App::Item::Image* const imgItem;
        Fk::Image processingImage;
        std::unique_ptr<Command::ApplyFilter> cBlackWhite;
        QVector<std::shared_ptr<Command::ApplyFilter>> commands;
};
#endif // WGTFILTER_H
