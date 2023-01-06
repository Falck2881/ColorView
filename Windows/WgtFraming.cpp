#include "WgtFraming.h"
#include "ui_WgtFraming.h"
#include "ItemImage.h"
#include "Image.h"
#include <QPixmap>

WinFrames::WinFrames(App::Item::Image* const imageItem) :
    ui(new Ui::WinFrames),
    imageItem{imageItem}
{
    ui->setupUi(this);
    ui->tabWidget->setTabText(0,"Page 1");
    ui->tabWidget->setTabText(1,"Page 2");
    initializeCommands();
    connect();
}

void WinFrames::initializeCommands()
{
    QVector<QString> listNameFile{":/ImgFrames/BlueFrame.png",":/ImgFrames/ClassicFrame.png",
                                  ":/ImgFrames/FrameTree.png",":/ImgFrames/GoldFrame.png",
                                  ":/ImgFrames/LineFrame.png",":/ImgFrames/Painting.png",
                                  ":/ImgFrames/SpottedFrame.png",":/ImgFrames/RedFrame.png",
                                  ":/ImgFrames/SheetFrame.png",":/ImgFrames/Vintag.png"};

    auto iter{listNameFile.begin()};

    for(; iter < listNameFile.end(); ++iter)
        commands.push_back(std::make_shared<Command::ApplyFrame>(*iter,this));

}

void WinFrames::connect()
{
    QVector<QPushButton*> buttons{ui->buttonBlueFrame,ui->buttonClassicFrame,
                                 ui->buttonFrameTree, ui->buttonGoldFrame,
                                 ui->buttonLinesFrame, ui->buttonPainting,
                                 ui->buttonSpottedFrame, ui->buttonRedFrame,
                                 ui->buttonSheetFrame, ui->buttonVintagFrame};

    for(qsizetype i = 0; i < buttons.size(); ++i)
        QObject::connect(buttons.at(i), &QPushButton::clicked,
                         commands.at(i).get(), &Command::ApplyFrame::execute);

    QObject::connect(ui->buttonCancel, &QPushButton::clicked, this, &WinFrames::show);
    QObject::connect(ui->buttonApply, &QPushButton::clicked, this, &WinFrames::apply);
}

void WinFrames::apply()
{
    imageItem->saveModifiedImage(this);
}

void WinFrames::updateBySourceImage(Fk::Image image)
{
    updateContantFrames();
    updateMainFrame(image);
    updateCommands(image);
}

void WinFrames::updateContantFrames()
{
    QVector<QLabel*> listFrames{ui->labelBlueFrame,ui->labelClassicFrame,
                               ui->labelTreeFrame,ui->labelGoldFrame,
                               ui->labelLinesFrame,ui->labelPaintingFrame,
                               ui->labelSpottedFrame,ui->labelRedFrame,
                               ui->labelSheetFrame,ui->labelVintagFrame};

    QVector<QString> listNameFile{":/ImgFrames/BlueFrame.png",":/ImgFrames/ClassicFrame.png",
                                  ":/ImgFrames/FrameTree.png",":/ImgFrames/GoldFrame.png",
                                  ":/ImgFrames/LineFrame.png",":/ImgFrames/Painting.png",
                                  ":/ImgFrames/SpottedFrame.png",":/ImgFrames/RedFrame.png",
                                  ":/ImgFrames/SheetFrame.png",":/ImgFrames/Vintag.png"};

    QImage frameImg;

    for(qsizetype i = 0; i < listFrames.size(); ++i)
    {
        frameImg.load(listNameFile.at(i));
        quint32 width = listFrames.at(i)->size().width();
        quint32 height = listFrames.at(i)->size().height();
        frameImg = frameImg.scaled(width,height);

        listFrames.at(i)->setPixmap(QPixmap::fromImage(frameImg));
    }

}

void WinFrames::updateMainFrame(Fk::Image image)
{
    quint32 width = ui->labelCurrentImage->width();
    quint32 height = ui->labelCurrentImage->height();
    image.scaled(width,height);
    ui->labelCurrentImage->setPixmap(image.pixmap());
}

void WinFrames::updateCommands(Fk::Image image)
{
    for(auto command: commands)
        command->setCurrentImage(image);
}

void WinFrames::setModifiedImage(Fk::Image modifiedImage)
{
    updateMainFrame(modifiedImage);
    imageAfterAddedFrame = modifiedImage;
}

Fk::Image WinFrames::getModifiedImage() const
{
    return imageAfterAddedFrame;
}

WinFrames::~WinFrames()
{
    delete ui;
}
