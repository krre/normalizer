cmake_minimum_required(VERSION 3.22)

project(normalizer VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets)
qt_standard_project_setup()

set(PROJECT_SOURCES
        main.cpp
        MainWindow.cpp
        MainWindow.h
)

qt_add_executable(normalizer
    ${PROJECT_SOURCES}
    core/Constants.h
    ../README.md
)

target_link_libraries(normalizer PRIVATE Qt6::Widgets)

set_target_properties(normalizer PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER normalizer.dev
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

install(TARGETS normalizer
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
