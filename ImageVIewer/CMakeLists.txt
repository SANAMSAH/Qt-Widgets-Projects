cmake_minimum_required(VERSION 3.16)
project(ImageVIewer LANGUAGES CXX)

include(qt.cmake)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core)
find_package(Qt${QT_VERSION_MAJOR}
    COMPONENTS
        Core
        Gui
        Widgets
)
qt_standard_project_setup()

# qt_standard_project_setup() enables AUTOMOC and AUTOUIC, but NOT AUTORCC.
# Without this, resources.qrc is never compiled by rcc, so the :/Icon/*.png
# images are missing at runtime (Qt Designer still shows them because it reads
# the PNG files directly from disk). This is why toolbar buttons showed text only.
set(CMAKE_AUTORCC ON)

set(PROJECT_SOURCES
    main.cpp
    ImageVIewer.ui
    ImageVIewer.h
    ImageVIewer.cpp
    resources.qrc
)

qt_add_executable(${PROJECT_NAME} ${PROJECT_SOURCES})

set_target_properties(${PROJECT_NAME}
    PROPERTIES
        WIN32_EXECUTABLE TRUE
)

target_link_libraries(${PROJECT_NAME}
    PUBLIC
        Qt::Core
        Qt::Gui
        Qt::Widgets
)

