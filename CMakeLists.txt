cmake_minimum_required(VERSION 3.18)

project(ProjectColorView VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets Core Gui)

qt_add_resources(IMG "${CMAKE_CURRENT_SOURCE_DIR}/Image/Img.qrc")
qt_add_resources(DATA "${CMAKE_CURRENT_SOURCE_DIR}/Sources/Data.qrc")

set(WINDOWS_SRC Windows/MainWindow.h Windows/MainWindow.cpp
                Windows/WgtImgProperty.h
                Windows/WgtImgProperty.cpp
                Windows/WgtImgProperty.ui
                Windows/WgtFilter.h
                Windows/WgtFilter.cpp
                Windows/WgtFilter.ui
                Windows/WgtFraming.h
                Windows/WgtFraming.cpp
                Windows/WgtFraming.ui
                Windows/WgtSaveImg.h
                Windows/WgtSaveImg.cpp
                Windows/WgtSaveImg.ui)

set(PROJECT_SOURCES     main.cpp
                        Sources/History.h
                        Sources/ConversionColor.h
                        Sources/AveragingColor.h
                        Sources/AveragingColor.cpp
                        Sources/MatrixFilter.h
                        Sources/MatrixFilter.cpp
                        Sources/ThreadProcessingImages.h
                        Sources/ThreadProcessingImages.cpp
                        Sources/SetConversions.h Sources/SetConversions.cpp
                        Sources/Command.h
                        Sources/SCApplyDepth.h Sources/SCApplyDepth.cpp
                        Sources/SCApplyFilter.h Sources/SCApplyFilter.cpp
                        Sources/SCApplyFrame.h Sources/SCApplyFrame.cpp
                        Sources/Items.h Sources/Items.cpp
                        Sources/Content.h Sources/Content.cpp
                        Sources/ContentItemFile.h Sources/ContentItemFile.cpp
                        Sources/ContentItemEdit.h Sources/ContentItemEdit.cpp
                        Sources/ContentItemImage.h Sources/ContentItemImage.cpp
                        Sources/ContentItemPage.h Sources/ContentItemPage.cpp
                        Sources/ItemFile.h Sources/ItemFile.cpp
                        Sources/ItemEdit.h Sources/ItemEdit.cpp
                        Sources/ItemImage.h Sources/ItemImage.cpp
                        Sources/ItemPage.h Sources/ItemPage.cpp
                        Sources/Board.h Sources/Board.cpp
                        Sources/Image.h Sources/Image.cpp   
                        )

if(WIN32)
    add_executable(ProjectColorView WIN32 ${PROJECT_SOURCES}
                                          ${IMG}
                                          ${DATA}
                                          ${WINDOWS_SRC}
                                          )
else()
    add_executable(ProjectColorView ${PROJECT_SOURCES}      
                                    ${IMG}
                                    ${DATA}
                                    ${WINDOWS_SRC}
                                    )
endif()

target_include_directories(ProjectColorView PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/Windows"
                                                    "${CMAKE_CURRENT_SOURCE_DIR}/Sources")

target_link_libraries(ProjectColorView PRIVATE Qt6::Widgets
                                               Qt6::Core
                                               Qt6::Gui)




#Connecting the library GTest



include(FetchContent)
FetchContent_Declare(googletest
                     URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip)

file(GLOB_RECURSE all_src_cpp "${CMAKE_CURRENT_SOURCE_DIR}/Windows/*.cpp"
                              "${CMAKE_CURRENT_SOURCE_DIR}/Sources/*.cpp")

file(GLOB_RECURSE all_src_hpp "${CMAKE_CURRENT_SOURCE_DIR}/Windows/*.h"
                              "${CMAKE_CURRENT_SOURCE_DIR}/Sources/*.h")

file(GLOB_RECURSE all_test_windows "${CMAKE_CURRENT_SOURCE_DIR}/TestingColorView/TestingWindows/*.cpp")

file(GLOB_RECURSE all_test_sources "${CMAKE_CURRENT_SOURCE_DIR}/TestingColorView/TestingSources/test_itemfile.cpp")

set(AllTestsColorView TestingColorView/test_main.cpp
                  ${all_src_cpp}
                  ${all_src_hpp}
                  ${all_test_windows}
                  ${all_test_sources})

enable_testing()

add_executable(TestColorView ${AllTestsColorView} ${DATA} ${IMG})

target_include_directories(TestColorView PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/Windows"
                                                 "${CMAKE_CURRENT_SOURCE_DIR}/Sources"
                                                 )

target_link_libraries(TestColorView PRIVATE GTest::gtest GTest::gtest_main
                                            Qt6::Widgets Qt6::Core)

# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)


set_target_properties(ProjectColorView PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

