cmake_minimum_required(VERSION 3.16)

project(TaskManager VERSION 1.0 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

file(GLOB_RECURSE TASK_HEADERS ${PROJECT_SOURCE_DIR}/include/*.hpp)
file(GLOB_RECURSE TASK_SOURCES ${PROJECT_SOURCE_DIR}/src/*.cpp)

# By default gui version not usage
option(GUI "For use gui version of programm" OFF)

if(GUI)
    add_definitions(-DGUI)
endif(GUI)

set(PROJECT_SOURCES
        ${PROJECT_SOURCE_DIR}/src/gui/mainwindow.ui
        ${TASK_HEADERS}
        ${TASK_SOURCES}
        main.cpp
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(TaskHandler
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
)
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET TaskHandler APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(TaskHandler SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(TaskHandler
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(TaskHandler PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
target_include_directories(TaskHandler PUBLIC ${PROJECT_SOURCE_DIR}/include)

set_target_properties(TaskHandler PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

install(TARGETS TaskHandler
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(TaskHandler)
endif()
