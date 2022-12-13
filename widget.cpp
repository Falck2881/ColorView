#include "widget.h"
#include "Image.h"
#include "InitColorImg.h"
#include "InitBlackWhiteImg.h"
#include "./ui_widget.h"
#include <QBuffer>
#include <QIODevice>

Widget::Widget(QWidget *parent):
    QWidget(parent)
    ,ui(new Ui::Widget),
    showImgInColor(std::make_unique<Fk::Command::ShowImage>
                   (
                       this,
                       std::make_shared<Fk::Init::ColorImg>(QString(":/ship.bmp"))
                   )
                  ),
    showImgInBlackWhite(std::make_unique<Fk::Command::ShowImage>
                        (
                            this,
                            std::make_shared<Fk::Init::BlackWhite>(QString(":/ship.bmp"))
                        )
                       )
{
    ui->setupUi(this);
    ui->labelImg->setPixmap(QPixmap(":/imgNotFound.png"));
    connectWithCommands();
}

void Widget::setPropertyImage(Fk::Image image)
{
    ui->labelImg->setPixmap(QPixmap(image.nameFile()));
    ui->widthImg->setText(image.width());
    ui->hightImg->setText(image.hight());
    ui->numsUseColors->setText(image.numberColor());
    ui->numBitOnPix->setText(image.numberBitOnPix());
    ui->sizeImgInByte->setText(image.sizeImgInByte());
    ui->formatFile->setText(image.formatFile());
    ui->nameFile->setText(image.nameFile());
}

void Widget::connectWithCommands() const
{
    QObject::connect(ui->buttInColor, &QPushButton::clicked,
                     showImgInColor.get(), &Fk::Base::Command::execute);
    QObject::connect(ui->buttInBlackWight, &QPushButton::clicked,
                     showImgInBlackWhite.get(), &Fk::Base::Command::execute);

}

Widget::~Widget()
{
    delete ui;
}

