#include "ItemFile.h"
#include "Image.h"
#include "MainWindow.h"
#include <QFileDialog>
#include <QVector>
#include <QDir>
#include <QMessageBox>
#include <QApplication>
#define NDEBUG
#include <assert.h>

App::Item::File::File(App::MainWindow* const mainWin):
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
    const QString pathToFile = QFileDialog::getOpenFileName(mainWindow, "Open File Image",
                                                             QDir::homePath(),"*.bmp ;; *.png ;; *.jpg");
    if(pathToFile.contains("bmp")){
        mainWindow->setFileInEachObserver(Fk::Image(pathToFile,"bmp"));
    }
    else if(pathToFile.contains("jpg")){
        mainWindow->setFileInEachObserver(Fk::Image(pathToFile,"jpg"));
    }
    else if(pathToFile.contains("png")){
        mainWindow->setFileInEachObserver(Fk::Image(pathToFile,"png"));
    }
}

void App::Item::File::save()
{
    assert(indexOnFile != -1);
    auto image = images.at(indexOnFile);

    if(image.save(image.absolutlePathToFile(),image.toCharFormat()))
        qDebug() << "File is success save";
    else
        qDebug() << "Cancel save a file";
}

void App::Item::File::saveAs()
{
    assert(indexOnFile != -1);
    winSaveImg->updateContent(images.at(indexOnFile));
    winSaveImg->show();
}

void App::Item::File::exit()
{
    QString message("Save all changes in files?\n");

    for(quint32 i = 0; i < images.size(); ++i)
        message += QString::number(i+1) + ": " + images.at(i).absolutlePathToFile() + "; \n";

    quint32 choice = QMessageBox::warning(mainWindow,"Warning",
                                          message,
                                          QMessageBox::Yes | QMessageBox::No);

    if(choice == QMessageBox::Yes)
    {
        for(auto& image: images)
            image.save(image.absolutlePathToFile(), image.toCharFormat());

        QApplication::quit();
    }
    else{
        qDebug() << "Cancel save changes in files and exit from program";
        QApplication::quit();
    }
}

void App::Item::File::updateContant(Fk::Image image)
{
    assert(indexOnFile != -1);

    images.replace(indexOnFile,image);
}

void App::Item::File::setContant(Fk::Image image)
{
    images.push_back(image);
}

void App::Item::File::checkStatyActions()
{
    QVector<QString> icons;
    if(images.empty()){
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


