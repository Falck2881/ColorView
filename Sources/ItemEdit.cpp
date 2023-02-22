#include "ItemEdit.h"
#include "MainWindow.h"
#include "ContentItemEdit.h"
#include <QKeySequence>
#include <QVector>

App::Item::Edit::Edit(App::MainWindow* const mainWin):
    App::Base::Item(std::make_unique<ContentItemEdit>()),
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

    currentBillboard = content->billboardInHistory();
    mainWindow->changesItems(this);
}

void App::Item::Edit::redo()
{
    content->redoModification();

    currentBillboard = content->billboardInHistory();
    mainWindow->changesItems(this);
}

std::shared_ptr<Billboard> App::Item::Edit::getBillboard() const
{
    return currentBillboard;
}

QMenu* App::Item::Edit::getMenu() const
{
    return mEdit.get();
}

QToolBar* App::Item::Edit::getToolBar() const
{
    return toolBar.get();
}

void App::Item::Edit::saveChangesInHistory(std::shared_ptr<Billboard> billboard)
{
    content->saveModifiedOnBillboard(billboard);
    currentBillboard = content->lastModifiedOnBillboard();
    mainWindow->changesItems(this);
}

void App::Item::Edit::checkStatyActions()
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
