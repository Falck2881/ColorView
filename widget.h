#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "ShowImage.h"
#include <memory>

namespace Fk {
    class Image;
}

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

    public:
        Widget(QWidget *parent = nullptr);
        ~Widget();
        void setPropertyImage(Fk::Image image);
    private:
        void setConnectWithCommand();
        void connectWithCommands() const;
    private:
        Ui::Widget *ui;
        std::unique_ptr<Fk::Command::ShowImage> showImgInColor;
        std::unique_ptr<Fk::Command::ShowImage> showImgInBlackWhite;
};
#endif // WIDGET_H
