#ifndef WGTSAVEIMG_H
#define WGTSAVEIMG_H

#include <QWidget>
#include "Image.h"
#include "SCApplyDepth.h"

namespace Ui {
class WinSaveImg;
}

class WinSaveImg : public QWidget
{
    Q_OBJECT

    public:
        WinSaveImg();
        void updateContent(Fk::Image image);
        void updateDepthColorsInImage(QImage::Format depthColor);
        ~WinSaveImg();
    private:
        void initializeCommands();
        void connect();
    private slots:
        void save();
        void changeStatusButtonSave(bool status);
    private:
        Fk::Image currentImage;
        QVector<std::shared_ptr<Command::ApplyDepth>> comApplysDepthColor;
        Ui::WinSaveImg *ui;
};

#endif // WGTSAVEIMG_H
