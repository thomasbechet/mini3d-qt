cmake_minimum_required(VERSION 3.5)

set(PROJ_NAME mini3d-qt)
set(RUST_DIR mini3d)

project(${PROJ_NAME} VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

set(PROJECT_SOURCES
    src/main.cpp
    src/bindingseditor.cpp
    src/mainwindow.cpp
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(mini3d-qt
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
else()
    if(ANDROID)
        add_library(${PROJ_NAME} SHARED
            ${PROJECT_SOURCES}
        )
    else()
        add_executable(${PROJ_NAME}
            ${PROJECT_SOURCES}
        )
    endif()
endif()

include(ExternalProject)
set_directory_properties(PROPERTIES EP_PREFIX ${PROJECT_BINARY_DIR}/RUST)
ExternalProject_Add(
    ${RUST_NAME}
    GIT_REPOSITORY https://github.com/thomasbechet/mini3d.git
    GIT_TAG "v1"
    BUILD_COMMAND cargo build COMMAND cargo build --release
    LOG_BUILD ON
)

add_dependencies(mini3d-qt mini3d)

target_link_libraries(mini3d-qt PRIVATE
    Qt${QT_VERSION_MAJOR}::Widgets
    debug "${PROJECT_SOURCE_DIR}/mini3d/target/debug/libmini3d.a"
    optimized "${PROJECT_SOURCE_DIR}/mini3d/target/release/libmini3d.a"
)

set_target_properties(mini3d-qt PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

install(TARGETS mini3d-qt
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(mini3d-qt)
endif()
