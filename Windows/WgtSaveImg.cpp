#include "WgtSaveImg.h"
#include "ui_WgtSaveImg.h"
#include <QFileDialog>
using namespace std;

WinSaveImg::WinSaveImg() :
    ui(new Ui::WinSaveImg)
{
    ui->setupUi(this);
    changeStatusButtonSave(false);
    initializeCommands();
    connect();
    setCursor(QCursor(QPixmap(":/Normal/cursor.png")));
}

void WinSaveImg::initializeCommands()
{
    QVector<QImage::Format> depthsColor{QImage::Format_Indexed8, QImage::Format_RGB16,
                                        QImage::Format_RGB888, QImage::Format_RGB32};

    QVector<QRadioButton*> buttons{ui->depth256Button, ui->depth16Button,
                                   ui->depth24Button, ui->depth32Button};

    for(qsizetype i{0}; i < buttons.size(); ++i)
        comApplysDepthColor.push_back(make_unique<Command::ApplyDepth>(this,buttons.at(i),depthsColor.at(i)));

}

void WinSaveImg::connect()
{
    QVector<QRadioButton*> buttonsChoiceDepth{ui->depth256Button, ui->depth16Button,
                                   ui->depth24Button, ui->depth32Button};

    for(qsizetype i{0}; i < comApplysDepthColor.size(); ++i)
    {
        QObject::connect(buttonsChoiceDepth.at(i), &QRadioButton::toggled,
                         comApplysDepthColor.at(i).get(), &Command::ApplyDepth::execute);

        QObject::connect(buttonsChoiceDepth.at(i), &QRadioButton::toggled,
                         this, &WinSaveImg::changeStatusButtonSave);
    }

    QObject::connect(ui->cancelButton, &QPushButton::clicked, this, &QWidget::hide);
    QObject::connect(ui->saveButton, &QPushButton::clicked, this, &WinSaveImg::save);
    QObject::connect(ui->saveButton, &QPushButton::clicked, this, &QWidget::hide);

}

void WinSaveImg::updateDepthColorsInImage(QImage::Format depthColor)
{
    currentImage.setDepthColor(depthColor);
    updateContent(currentImage);
}

void WinSaveImg::updateContent(Fk::Image image)
{
    image.scaled(ui->labelCurrentImg->width(), ui->labelCurrentImg->height());
    ui->labelCurrentImg->setAlignment(Qt::AlignCenter);
    ui->labelCurrentImg->setPixmap(image.pixmap());
    currentImage = image;
}

void WinSaveImg::changeStatusButtonSave(bool status)
{
    ui->saveButton->setEnabled(status);
}

void WinSaveImg::save()
{
    QString newFormat;
    const QString newAbsPathToFile = QFileDialog::getSaveFileName(this, "Save As", QDir::homePath(),
                                                                  "*.bmp;;*.png;;*.jpg;;*.jpeg;;",
                                                                  &newFormat, QFileDialog::DontUseNativeDialog);

    if(newFormat.contains("bmp"))
        currentImage.save(newAbsPathToFile, "bmp");
    else if(newFormat.contains("png"))
        currentImage.save(newAbsPathToFile, "png");
    else if(newFormat.contains("jpg"))
        currentImage.save(newAbsPathToFile, "jpg");
    else if(newFormat.contains("jpeg"))
        currentImage.save(newAbsPathToFile, "jpeg");
}


WinSaveImg::~WinSaveImg()
{
    delete ui;
}
