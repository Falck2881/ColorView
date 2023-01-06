#include "WgtImgProperty.h"
#include "Image.h"
#include "./ui_WgtImgProperty.h"
#include <QBuffer>
#include <QIODevice>

WinImgProperty::WinImgProperty():
    ui(new Ui::Property)
{
    ui->setupUi(this);
    this->move(500,400);
    this->setWindowFlag(Qt::WindowStaysOnTopHint);
    this->connect();
}

void WinImgProperty::setPropertyImage(Fk::Image image)
{
    ui->widthImg->setText(QString::number(image.width()));
    ui->hightImg->setText(QString::number(image.height()));
    ui->numsUseColors->setText(image.numberColor());
    ui->numBitOnPix->setText(image.numberBitOnPix());
    ui->sizeImgInByte->setText(image.sizeImgInByte());
    ui->formatFile->setText(image.toStrFormat());
    ui->nameFile->setText(image.nameFile());
}

void WinImgProperty::connect() const
{
    QObject::connect(ui->buttonOk, &QPushButton::clicked, this, &QWidget::hide);
}

WinImgProperty::~WinImgProperty()
{
    delete ui;
}

