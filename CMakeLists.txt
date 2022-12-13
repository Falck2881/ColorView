cmake_minimum_required(VERSION 3.18)

project(ProjectColorView VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets Core REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets REQUIRED)

qt6_add_resources(IMG "${CMAKE_CURRENT_SOURCE_DIR}/Img.qrc")

set(PROJECT_SOURCES
        main.cpp
        widget.cpp widget.h widget.ui
        Image.h Image.cpp
        Command.h
        ShowImage.h ShowImage.cpp
        InitializeImg.h InitializeImg.cpp
        InitColorImg.h InitColorImg.cpp
        InitBlackWhiteImg.h InitBlackWhiteImg.cpp
)

if(WIN32)
    add_executable(ProjectColorView WIN32 ${PROJECT_SOURCES} ${IMG})
else()
    add_executable(ProjectColorView ${PROJECT_SOURCES} ${IMG})
endif()

target_link_libraries(ProjectColorView PRIVATE Qt6::Widgets Qt6::Core)

set_target_properties(ProjectColorView PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(ProjectColorView)
endif()
