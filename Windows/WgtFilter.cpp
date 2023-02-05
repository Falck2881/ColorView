#include "WgtFilter.h"
#include "ui_WgtFilter.h"
#include "ItemImage.h"
#include <QLabel>
#include <QFile>


using namespace std;

WinFilter::WinFilter(App::Item::Image* const itemImage):
  ui(new Ui::Filter),
  imgItem(itemImage)

{
    ui->setupUi(this);
    initializeCommands();
    connect();
}

void WinFilter::initializeCommands()
{
    auto collectionFilters{collection.getFilters()};
    auto iterOnFilter = collectionFilters.begin();

    for(; iterOnFilter < collectionFilters.end(); ++iterOnFilter)
        comApplysFilters.push_back(make_shared<Command::ApplyFilter>(*iterOnFilter,this));

}

void WinFilter::connect()
{
    QVector<QPushButton*> buttonsChoiceFilter{ui->buttonForest,ui->buttonBlackWhite, ui->buttonPurply,
                                  ui->buttonEmerald, ui->buttonWarm,ui->buttonCool};

    for(qsizetype i{0}; i < comApplysFilters.size(); ++i)
        QObject::connect(buttonsChoiceFilter.at(i), &QPushButton::clicked,
                         comApplysFilters.at(i).get(), &Command::ApplyFilter::execute);

    QObject::connect(ui->buttonCancel, &QPushButton::clicked,
                     this, &QWidget::hide);
    QObject::connect(ui->buttonApply, &QPushButton::clicked,
                     this, &WinFilter::apply);
    QObject::connect(ui->buttonApply, &QPushButton::clicked,
                     this, &QWidget::hide);
}

void WinFilter::apply()
{
    imgItem->saveModifiedImage(this);
}

void WinFilter::setModifiedImage(Fk::Image newImageProcessing)
{
    updateMainFrame(newImageProcessing);
    processingImage = newImageProcessing;
}

void WinFilter::updateContant(Fk::Image image,  QVector<Fk::Image> processingImages)
{
    processingImage = image;
    updateContainFrames(processingImages);
    updateMainFrame(image);
    updateCommands(image);
}

void WinFilter::updateContainFrames(QVector<Fk::Image> processingImages)
{

    QVector<QLabel*> frames{ui->labelForest,ui->labelBlackWhite,ui->labelPunk,
                             ui->labelSaturation,ui->labelWarm,ui->labelCool};

    quint32 width, height;

    for(qsizetype i = 0; i < frames.size(); ++i)
    {
        width = frames.at(i)->width();
        height = frames.at(i)->height();
        processingImages[i].scaled(width,height);
        frames.at(i)->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
        frames.at(i)->setPixmap(processingImages.at(i).pixmap());
    }
}

void WinFilter::updateMainFrame(Fk::Image image)
{
    image.scaled(ui->labelImage->width(), ui->labelImage->height());
    ui->labelImage->setPixmap(image.pixmap());
}

void WinFilter::updateCommands(Fk::Image image)
{
    for(auto command: comApplysFilters)
        command->setCurrentImage(image);
}

void WinFilter::updateDepthColorsInImage(QImage::Format depthColor)
{
    processingImage.setDepthColor(depthColor);
}

Fk::Image WinFilter::getModifiedImage() const
{
    return processingImage;
}

WinFilter::~WinFilter()
{
    delete ui;
}
