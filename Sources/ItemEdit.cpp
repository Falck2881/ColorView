#include "ItemEdit.h"
#include "MainWindow.h"
#include <QKeySequence>
#include <QVector>
#define NDEBUG
#include <assert.h>

App::Item::Edit::Edit(App::MainWindow* const mainWin):
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
    assert(indexOnFile != -1);

    historyEdit[indexOnFile].decrement();

    imageInHistory = historyEdit.at(indexOnFile).file();
    mainWindow->changesItems(this);
}

void App::Item::Edit::redo()
{
    assert(indexOnFile != -1);

    historyEdit[indexOnFile].increment();
    imageInHistory = historyEdit.at(indexOnFile).file();
    mainWindow->changesItems(this);
}

Fk::Image App::Item::Edit::getCurrentImage() const
{
    return imageInHistory;
}

QMenu* App::Item::Edit::getMenu() const
{
    return mEdit.get();
}

QToolBar* App::Item::Edit::getToolBar() const
{
    return toolBar.get();
}

void App::Item::Edit::saveChangesInHistory(Fk::Image image)
{
    assert(indexOnFile != -1);

    historyEdit[indexOnFile].push_back(image);
    imageInHistory = historyEdit[indexOnFile].last();
    mainWindow->changesItems(this);
}

void App::Item::Edit::setContent(const Fk::Image&  image)
{
    historyEdit.push_back(FileModified::History<Fk::Image>{image});
}

void App::Item::Edit::checkStatyActions()
{
    QVector<QString> icons;

    if(historyEdit.empty()){
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
