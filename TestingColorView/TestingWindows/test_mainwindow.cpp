#include "gtest/gtest.h"
#include "MainWindow.h"
#include "ItemEdit.h"
#include "ItemFile.h"
#include "ItemImage.h"
#include "ItemPage.h"
#include <iostream>


TEST(MainWindow, checkAllObsevers)
{
    std::unique_ptr<App::MainWindow> mainWindow{std::make_unique<App::MainWindow>()};

    ASSERT_TRUE(mainWindow->observersExist());
}

TEST(MainWindow, setBoardInEachObserver)
{
    std::unique_ptr<App::MainWindow> mainWindow{std::make_unique<App::MainWindow>()};

    ASSERT_NO_THROW(mainWindow->setBillboardInEachObserver(std::make_pair<QString,QString>(":/imgNotFound.png", "png")));
}

TEST(MainWindow, changeIndexOnFile)
{
    std::unique_ptr<App::MainWindow> mainWindow{std::make_unique<App::MainWindow>()};
    const qint32 index{0};

    ASSERT_NO_THROW(mainWindow->changeIndex(index));
}
