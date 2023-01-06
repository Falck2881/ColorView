#include "WgtFilter.h"
#include "ui_WgtFilter.h"
#include "FilterImage.h"
#include "ItemImage.h"
#include "MatrixCalculateColor.h"
#include "AveragingColor.h"
#include <QLabel>

using namespace std;

WinFilter::WinFilter(App::Item::Image* const itemImage):
  ui(new Ui::Filter),
  imgItem(itemImage),
  applyBlackWhite{make_unique<Command::ApplyFilter>
       (make_shared<FilterImage>(make_shared<AveragingColor>()),this)}

{
    ui->setupUi(this);
    initializeCommands();
    connect();
}

void WinFilter::initializeCommands()
{

    QVector<QString> listNameFile{":/Forest.txt", ":/Sharpness.txt", ":/Saturation.txt",
                                  ":/Warm.txt", ":/Cool.txt"};

    auto iterStr = listNameFile.begin();

    for(; iterStr < listNameFile.end(); ++iterStr)
        commands.push_back(make_shared<Command::ApplyFilter>
                (make_shared<FilterImage>(make_shared<MatrixCalculateColor>(*iterStr)),this));

}

void WinFilter::connect()
{
    QVector<QPushButton*> buttons{ui->buttonForest,ui->buttonPunk,ui->buttonSaturation,
                                 ui->buttonWarm,ui->buttonCool};

    for(qsizetype i = 0; i < commands.size(); ++i)
        QObject::connect(buttons.at(i), &QPushButton::clicked,
                         commands.at(i).get(), &Command::ApplyFilter::execute);

    QObject::connect(ui->buttonBlackWhite, &QPushButton::clicked,
                     applyBlackWhite.get(), &Command::ApplyFilter::execute);
    QObject::connect(ui->buttonCancel, &QPushButton::clicked,
                     this, &QWidget::hide);
    QObject::connect(ui->buttonOk, &QPushButton::clicked,
                     this, &WinFilter::apply);
    QObject::connect(ui->buttonOk, &QPushButton::clicked,
                     this, &QWidget::hide);

}

void WinFilter::apply()
{
    imgItem->saveModifiedImage(this);
}

void WinFilter::setModifiedImage(Fk::Image modifiedImage)
{
    updateMainFrame(modifiedImage);
    imageAfterApplyFilter = modifiedImage;
}

void WinFilter::updateBySourceImage(Fk::Image image)
{
    updateContainFrames(image);
    updateMainFrame(image);
    updateCommands(image);
}

void WinFilter::updateContainFrames(Fk::Image image)
{
    QVector<Fk::Image> images{image,image,image,image,image,image};

    QVector<QLabel*> frames{ui->labelForest,ui->labelBlackWhite,ui->labelPunk,
                             ui->labelSaturation,ui->labelWarm,ui->labelCool};

    QVector<std::shared_ptr<Base::CalculateColor>> methodCalculateColor;
    methodCalculateColor << make_unique<MatrixCalculateColor>(":/Forest.txt") <<
                            make_unique<AveragingColor>() <<
                            make_unique<MatrixCalculateColor>(":/Sharpness.txt") <<
                            make_unique<MatrixCalculateColor>(":/Saturation.txt") <<
                            make_unique<MatrixCalculateColor>(":/Warm.txt") <<
                            make_unique<MatrixCalculateColor>(":/Cool.txt");


    for(qsizetype i = 0; i < frames.size(); ++i)
    {
        images[i].scaled(frames.at(i)->width()-15,frames.at(i)->height()-15);
        images[i].setFilter(make_shared<FilterImage>(methodCalculateColor.at(i)));
        frames.at(i)->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
        frames.at(i)->setPixmap(images[i].pixmap());
    }

}

void WinFilter::updateMainFrame(Fk::Image image)
{
    image.scaled(ui->labelImage->width(), ui->labelImage->height());
    ui->labelImage->setPixmap(image.pixmap());
}

void WinFilter::updateCommands(Fk::Image image)
{
    applyBlackWhite->setCurrentImage(image);

    for(auto command: commands)
        command->setCurrentImage(image);
}

Fk::Image WinFilter::getModifiedImage() const
{
    return imageAfterApplyFilter;
}

WinFilter::~WinFilter()
{
    delete ui;
}
