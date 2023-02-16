#include "gtest/gtest.h"
#include "MainWindow.h"
#include "ItemEdit.h"
#include "ItemFile.h"
#include "ItemImage.h"
#include "ItemPage.h"
#include <iostream>


TEST(MainWindow, appendObsevers)
{
    std::unique_ptr<App::MainWindow> mainWindow{std::make_unique<App::MainWindow>()};
    QList<std::shared_ptr<App::Base::Item>> observers;
    observers << std::make_shared<App::Item::Edit>(mainWindow.get()) << std::make_shared<App::Item::File>(mainWindow.get()) <<
              std::make_shared<App::Item::Image>(mainWindow.get()) << std::make_shared<App::Item::Page>(mainWindow.get());

    ASSERT_TRUE(mainWindow->observersOfExist());
}
