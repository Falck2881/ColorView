#ifndef WGTFRAMES_H
#define WGTFRAMES_H

#include <QWidget>
#include "SCApplyFrame.h"
#include "Image.h"

namespace App::Item {
    class Image;
}

namespace Ui {
class WinFrames;
}

class WinFrames : public QWidget
{
    Q_OBJECT

    public:
        explicit WinFrames(App::Item::Image* const imageItem);
        void updateBySourceImage(const Fk::Image& image);
        void setModifiedImage(const Fk::Image& modifiedImage);
        Fk::Image getModifiedImage() const;
        ~WinFrames();
    private:
        void setPropertyTabWidget();
        void initializeCommands();
        void connect();
        void updateContantFrames();
        void updateMainFrame(Fk::Image image);
        void updateCommands(const Fk::Image& image);
    private slots:
        void apply();
        void choiceRandomFrame();
    private:
        Ui::WinFrames *ui;
        App::Item::Image* const imageItem;
        Fk::Image imageAfterAddedFrame;
        QVector<std::shared_ptr<Command::ApplyFrame>> commands;
};

#endif // WGTFRAMES_H
