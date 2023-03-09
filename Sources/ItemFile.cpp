#include "ItemFile.h"
#include "Image.h"
#include "MainWindow.h"
#include <utility>
#include <QFileDialog>
#include <QVector>
#include <QDir>
#include <QMessageBox>
#include <QApplication>
#include <QDebug>

App::Item::File::File(App::MainWindow* const mainWin):
    content(std::make_unique<Content>()),
    aExite{std::make_unique<QAction>("&Exit")},
    aSaveFileAs{std::make_unique<QAction>("&Save As ...")},
    aSaveFile{std::make_unique<QAction>("&Save")},
    aOpenFile{std::make_unique<QAction>("&Open")},
    mFile{std::make_unique<QMenu>("&File")},
    toolBar{std::make_unique<QToolBar>()},
    mainWindow{mainWin},
    winSaveImg{std::make_unique<WinSaveImg>()}
{
    mainWindow->appand(this);
    initializeEachAction();
    connectWithCommand();
}

void App::Item::File::initializeEachAction()
{
    aOpenFile->setShortcut(QKeySequence("CTRL+O"));
    aOpenFile->setWhatsThis("Open a file from specified you folder");
    aOpenFile->setIcon(QIcon(":/Normal/Open Image.bmp"));
    mFile->addAction(aOpenFile.get());
    toolBar->addAction(aOpenFile.get());
    aSaveFileAs->setShortcut(QKeySequence("Shift+CTRL+S"));
    aSaveFileAs->setWhatsThis("Save an image in specified the folder");
    aSaveFileAs->setIcon(QIcon(":/Disabled/Save as.bmp"));
    aSaveFile->setShortcut(QKeySequence("CTRL+S"));
    aSaveFile->setWhatsThis("Save an image.");
    aSaveFile->setIcon(QIcon(":/Disabled/Save.bmp"));

    QList<QAction*> listAction{aSaveFile.get(),aSaveFileAs.get()};

    for(auto action: listAction){
        action->setEnabled(false);
        mFile->addAction(action);
        toolBar->addAction(action);
    }

    aExite->setShortcut(QKeySequence("CTRL+Q"));
    aExite->setWhatsThis("Exit from application");
    mFile->addAction(aExite.get());
}

void App::Item::File::connectWithCommand()
{
    QObject::connect(aOpenFile.get(), &QAction::triggered, this, &App::Item::File::open);

    QObject::connect(aSaveFile.get(), &QAction::triggered, this, &App::Item::File::save);

    QObject::connect(aSaveFileAs.get(), &QAction::triggered, this, &App::Item::File::saveAs);

    QObject::connect(aExite.get(), &QAction::triggered, this, &App::Item::File::exit);
}

void App::Item::File::open()
{
    const QString pathToFile = getPathToFile();
    if(pathToFile != ""){
        mainWindow->setBillboardInEachObserver(pathToFile);
        mainWindow->setActivityTheWitgetsInEachObserver();
    }
}

QString App::Item::File::getPathToFile() const
{
    return QFileDialog::getOpenFileName(mainWindow, "Open File Image",
                                        QDir::homePath(),"*.bmp *.png *.jpg *.jpeg *.pcx");
}

void messageWhenSaveIntoPCXFormat(QWidget* const parrent);

void App::Item::File::save()
{
    Fk::Image image = content->image();
    QString format{image.toFormat()};

    if(format.contains("bmp"))
        image.save(image.absolutlePathToFile(), "bmp");
    else if(format.contains("png"))
        image.save(image.absolutlePathToFile(), "png");
    else if(format.contains("jpg"))
        image.save(image.absolutlePathToFile(), "jpg");
    else if(format.contains("jpeg"))
        image.save(image.absolutlePathToFile(), "jpeg");
    else if(format.contains("pcx"))
        messageWhenSaveIntoPCXFormat(mainWindow);
}

void messageWhenSaveIntoPCXFormat(QWidget* const parrent)
{
    QString message("Sorry image in format 'pcx' cannot \n"
                    "       save in that application.   \n"
                    "You can save image in other format:\n"
                    "          BMP,JPG,JPEG,PNG         \n");
    QMessageBox messageBox(QMessageBox::Question,"Save",message,QMessageBox::Ok,parrent);

    messageBox.exec();
}

void App::Item::File::saveAs()
{
    winSaveImg->updateContent(content->image());
    winSaveImg->show();
}

void App::Item::File::setIndex(const qint32 newIndex)
{
    content->setIndex(newIndex);
}

void App::Item::File::setContent(const QString& newContent)
{
    content->setContent(newContent);
}

void App::Item::File::updateContent(std::shared_ptr<Billboard> billboard)
{
    content->updateContent(billboard);
}

void App::Item::File::removeContent(const qint32 index)
{
    content->removeContent(index);
}

void App::Item::File::exit()
{
    QString message("Save all changes in files?\n");

    for(quint32 i = 0; i < content->sizeBillboard(); ++i){
        Fk::Image image{content->image()};
        message += QString::number(i+1) + ": " + image.absolutlePathToFile() + "; \n";
    }

    quint32 choice = QMessageBox::warning(mainWindow,"Warning",
                                          message,
                                          QMessageBox::Yes | QMessageBox::No);

    if(choice == QMessageBox::Yes)
    {
        for(auto& image: content->images())
            image.save(image.absolutlePathToFile(), image.toFormat());

        QApplication::quit();
    }
    else{
        qDebug() << "Cancel save changes in files and exit from program";
        QApplication::quit();
    }
}

void App::Item::File::setActivityOfWidgets()
{
    QVector<QString> icons;
    if(content->isBillboardEmpty()){
        icons << ":/Disabled/Save.bmp" << ":/Disabled/Save as.bmp" ;
        setPropertyActions(false,icons);
    }
    else{
        icons << ":/Normal/Save.bmp" << ":/Normal/Save as.bmp";
        setPropertyActions(true, icons);
    }
}


void App::Item::File::setPropertyActions(bool value, const QVector<QString>& icons)
{
    QList<QAction*> listAction{aSaveFile.get(),aSaveFileAs.get()};

    for(quint32 index = 0; index < listAction.size(); ++index)
    {
        listAction.at(index)->setIcon(QIcon(icons.at(index)));
        listAction.at(index)->setEnabled(value);
    }
}

QMenu* App::Item::File::getMenu() const
{
    return mFile.get();
}

QToolBar* App::Item::File::getToolBar() const
{
    return toolBar.get();
}


