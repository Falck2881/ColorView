#include "ItemEdit.h"
#include "MainWindow.h"
#include <QKeySequence>
#include <QVector>
#include <QMessageBox>

bool warrning(const Fk::Image& image, App::MainWindow* const mainWindow);

App::Item::Edit::Edit(App::MainWindow* const mainWin):
    content(std::make_unique<ContentItemEdit>()),
    aUndo{std::make_unique<QAction>("&Undo")},
    aRedo{std::make_unique<QAction>("&Redo")},
    mEdit{std::make_unique<QMenu>("&Edit")},
    toolBar{std::make_unique<QToolBar>()},
    mainWindow{mainWin}
{
    mainWindow->appand(this);
    initializeEachAction();
    connectWithCommand();
}

void App::Item::Edit::initializeEachAction()
{
    aUndo->setShortcut(QKeySequence("CTRL+Z"));
    aUndo->setWhatsThis("Return how a before.");
    aUndo->setIcon(QIcon(":/Disabled/Undo.bmp"));
    aUndo->setEnabled(false);
    toolBar->addAction(aUndo.get());
    aRedo->setShortcut(QKeySequence("CTRL+X"));
    aRedo->setWhatsThis("Return how a was.");
    aRedo->setIcon(QIcon(":/Disabled/Redo.bmp"));
    aRedo->setEnabled(false);
    toolBar->addAction(aRedo.get());

    mEdit->addAction(aUndo.get());
    mEdit->addAction(aRedo.get());
}

void App::Item::Edit::connectWithCommand()
{
    QObject::connect(aUndo.get(), &QAction::triggered, this, &App::Item::Edit::undo);
    QObject::connect(aRedo.get(), &QAction::triggered, this, &App::Item::Edit::redo);
}

void App::Item::Edit::undo()
{
    content->undoModification();

    currentImage = content->imageInHistory();
    writeNoteAboutAction(QString("Wait, goes update :") + currentImage.nameFile());
    mainWindow->updateMessageInStatusBar(this);
    mainWindow->changeContentOfItems(this);
}

void App::Item::Edit::redo()
{
    content->redoModification();

    currentImage = content->imageInHistory();
    writeNoteAboutAction(QString("Wait, goes update :") + currentImage.nameFile());
    mainWindow->updateMessageInStatusBar(this);
    mainWindow->changeContentOfItems(this);
}

void App::Item::Edit::setIndex(const qint32 newIndex)
{
    content->setIndex(newIndex);
}

void App::Item::Edit::setContent(const Fk::Image& newContent)
{
    content->setContent(newContent);
}

void App::Item::Edit::removeContent(const qint32 index)
{
    content->removeContent(index);
}

const Fk::Image& App::Item::Edit::getImage() const
{
    return currentImage;
}

QMenu* App::Item::Edit::getMenu() const
{
    return mEdit.get();
}

QToolBar* App::Item::Edit::getToolBar() const
{
    return toolBar.get();
}

void App::Item::Edit::saveModifiedImageInHistory(const Fk::Image& image)
{
    content->saveModifiedOnImage(image);
    currentImage = content->lastModifiedOnImage();
    writeNoteAboutAction(QString("Wait, goes update :") + currentImage.nameFile());
    mainWindow->updateMessageInStatusBar(this);
    mainWindow->changeContentOfItems(this);
}

void App::Item::Edit::saveDrawnImageModified(const Fk::Image& image)
{
    content->saveModifiedOnImage(image);
    currentImage = content->lastModifiedOnImage();
    writeNoteAboutAction(QString("Wait, goes update :") + currentImage.nameFile());
    mainWindow->updateMessageInStatusBar(this);
}

void App::Item::Edit::checkHistoryModified(const qint32 index)
{
    auto historys = content->atHistory(index);
    Fk::Image img{historys.image()};

    if(warrning(img, mainWindow))
        mainWindow->closePageAndSave();

}

bool warrning(const Fk::Image& image, App::MainWindow* const mainWindow)
{
    QString message("You want closed the file: " + image.nameFile() + ".\n" +
                    "Save the modification of file ?");

    QMessageBox messageBox(QMessageBox::Question, "Save Modification?", message,
                           QMessageBox::No|QMessageBox::Save, mainWindow);
    quint32 choice = messageBox.exec();

    if(choice == QMessageBox::Save)
        return true;
    else
        return false;
}

void App::Item::Edit::setActivityOfWidgets()
{
    QVector<QString> icons;

    if(content->isHistoryEmpty()){
        icons << ":/Disabled/Redo.bmp" << ":/Disabled/Undo.bmp";
        setPropertyActions(false,icons);
    }
    else{
        icons << ":/Normal/Redo.bmp" << ":/Normal/Undo.bmp";
        setPropertyActions(true,icons);
    }
}

void App::Item::Edit::setPropertyActions(bool value, const QVector<QString>& icons)
{
    QList<QAction*> listActions{aRedo.get(),aUndo.get()};

    for(quint32 index = 0; index < listActions.size(); ++index)
    {
        listActions.at(index)->setIcon(QIcon(icons.at(index)));
        listActions.at(index)->setEnabled(value);
    }
}
