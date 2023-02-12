#ifndef WGTIMGPROPERTY_H
#define WGTIMGPROPERTY_H

#include <QWidget>
#include <memory>

namespace Fk {
    class Image;
}

QT_BEGIN_NAMESPACE
namespace Ui { class Property; }
QT_END_NAMESPACE

class WinImgProperty : public QWidget
{
    Q_OBJECT

    public:
        WinImgProperty();
        ~WinImgProperty();
        void setPropertyImage(const Fk::Image& image);
    private:
        void connect() const;
    private:
        Ui::Property *ui;

};
#endif // WGTIMGPROPERTY_H
