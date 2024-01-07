#ifndef WGTSELECTWIDTHPENCIL_H
#define WGTSELECTWIDTHPENCIL_H

#include <QDialog>
#include <QPushButton>
#include <memory>
#include <QVBoxLayout>

class WgtSelectWidthPencil: public QDialog
{
    Q_OBJECT
    public:
        WgtSelectWidthPencil(QWidget* parent);
    signals:
        void updateWidthPencil(qint32 width);
    private:
        void initializeWgt();
        void initializeButtons();
        void connectToEvents();
    private slots:
        void choiceIn5px();
        void choiceIn10px();
        void choiceIn15px();
        void choiceIn20px();
    private:
        QPushButton* button5px;
        QPushButton* button10px;
        QPushButton* button15px;
        QPushButton* button20px;
        QVBoxLayout* layout;
};

#endif // WGTSELECTWIDTHPENCIL_H
