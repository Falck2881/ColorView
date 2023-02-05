#ifndef WGTFILTER_H
#define WGTFILTER_H

#include <QWidget>
#include "SCApplyDepth.h"
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
        void setModifiedImage(Fk::Image modifiedImage);
        void updateDepthColorsInImage(QImage::Format depthColor);
        void updateContant(const Fk::Image image,
                           const QVector<Fk::Image> imagesAfterProcessing);
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
        QVector<std::shared_ptr<Command::ApplyFilter>> comApplysFilters;
};
#endif // WGTFILTER_H
