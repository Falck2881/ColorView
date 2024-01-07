#include "WgtSelectWidthPencil.h"
#include <QVBoxLayout>
#include <QRadioButton>
#include <QPixmap>
#include <QObject>

WgtSelectWidthPencil::WgtSelectWidthPencil(QWidget* parent):
    QDialog(parent),
    button5px{new QPushButton()},
    button10px{new QPushButton()},
    button15px{new QPushButton()},
    button20px{new QPushButton()}
{
    setWindowTitle("Select width of pencil");
    setFixedSize(300,300);
    setCursor(QCursor(QPixmap(":/Normal/cursor.png")));
    initializeButtons();
    initializeWgt();
    connectToEvents();
}

void WgtSelectWidthPencil::initializeButtons()
{
    QList<QPushButton*> buttons{button5px, button10px, button15px, button20px};
    QList<QString> nameFiles{":/Normal/width5px.png",":/Normal/width10px.png",":/Normal/width15px.png",":/Normal/width20px.png"};

    for (int index = 0; index < buttons.size(); ++index){
        buttons.at(index)->setIcon(QPixmap(nameFiles.at(index)));
        buttons.at(index)->setIconSize(QSize(250,50));
    }
}

void WgtSelectWidthPencil::initializeWgt()
{
    QVBoxLayout* layout = new QVBoxLayout(this);

    layout->setSpacing(15);
    layout->addWidget(button5px, 0, Qt::AlignVCenter);
    layout->addWidget(button10px, 1, Qt::AlignVCenter);
    layout->addWidget(button15px, 2, Qt::AlignVCenter);
    layout->addWidget(button20px, 3, Qt::AlignVCenter);

    setLayout(layout);
}

void WgtSelectWidthPencil::connectToEvents()
{
    QObject::connect(button5px, &QPushButton::clicked, this, &WgtSelectWidthPencil::choiceIn5px);
    QObject::connect(button10px, &QPushButton::clicked, this, &WgtSelectWidthPencil::choiceIn10px);
    QObject::connect(button15px, &QPushButton::clicked, this, &WgtSelectWidthPencil::choiceIn15px);
    QObject::connect(button20px, &QPushButton::clicked, this, &WgtSelectWidthPencil::choiceIn20px);
}

void WgtSelectWidthPencil::choiceIn5px()
{
    hide();
    emit updateWidthPencil(5);
}

void WgtSelectWidthPencil::choiceIn10px()
{
    hide();
    emit updateWidthPencil(10);
}

void WgtSelectWidthPencil::choiceIn15px()
{
    hide();
    emit updateWidthPencil(15);
}

void WgtSelectWidthPencil::choiceIn20px()
{
    hide();
    emit updateWidthPencil(20);
}
