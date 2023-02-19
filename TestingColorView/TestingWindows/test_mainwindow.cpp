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

    mainWindow->setBillboardInEachObserver(std::make_shared<Fk::Image>(":/ship.bmp","bmp"));


}
