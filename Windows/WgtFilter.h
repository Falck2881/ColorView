#ifndef WGTFILTER_H
#define WGTFILTER_H

#include <QWidget>
#include "SCApplyFilter.h"
#include "Image.h"

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
        void updateBySourceImage(Fk::Image image);
        void setModifiedImage(Fk::Image modifiedImage);
    private:
        void initializeCommands();
        void connect();
        void updateContainFrames(Fk::Image image);
        void updateMainFrame(Fk::Image image);
        void updateCommands(Fk::Image image);
    private slots:
        void apply();
    private:
        Ui::Filter *ui;
        App::Item::Image* const imgItem;
        Fk::Image imageAfterApplyFilter;
        std::shared_ptr<Command::ApplyFilter> applyBlackWhite;
        QVector<std::shared_ptr<Command::ApplyFilter>> commands;
};
#endif // WGTFILTER_H
