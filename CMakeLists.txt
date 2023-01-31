cmake_minimum_required(VERSION 3.18)

project(ProjectColorView VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets Core Gui)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets Core Gui)

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
                Windows/WgtFraming.ui)

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
                        Sources/SCApplyFilter.h Sources/SCApplyFilter.cpp
                        Sources/SCApplyFrame.h Sources/SCApplyFrame.cpp
                        Sources/Items.h
                        Sources/ItemFile.h Sources/ItemFile.cpp
                        Sources/ItemEdit.h Sources/ItemEdit.cpp
                        Sources/ItemImage.h Sources/ItemImage.cpp
                        Sources/ItemPage.h Sources/ItemPage.cpp
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

target_link_libraries(ProjectColorView PRIVATE Qt${QT_VERSION_MAJOR}::Widgets
                                               Qt${QT_VERSION_MAJOR}::Core
                                               Qt${QT_VERSION_MAJOR}::Gui)

set_target_properties(ProjectColorView PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

