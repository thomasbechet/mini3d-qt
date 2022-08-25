cmake_minimum_required(VERSION 3.5)

set(MINI3D_NAME mini3d)

project(mini3d-qt VERSION 0.1 LANGUAGES CXX)

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
        add_library(${PROJECT_NAME} SHARED
            ${PROJECT_SOURCES}
        )
    else()
        add_executable(${PROJECT_NAME}
            ${PROJECT_SOURCES}
        )
    endif()
endif()

include(ExternalProject)
ExternalProject_Add(
    ${MINI3D_NAME}
    BUILD_BYPRODUCTS  "${PROJECT_SOURCE_DIR}/${MINI3D_NAME}/target/debug/${MINI3D_NAME}.dll.lib"
    GIT_REPOSITORY    "https://github.com/thomasbechet/mini3d.git"
    BUILD_COMMAND     cargo build
    SOURCE_DIR        "${PROJECT_SOURCE_DIR}/${MINI3D_NAME}"
    UPDATE_COMMAND    ""
    CONFIGURE_COMMAND ""
    INSTALL_COMMAND   ""
    TEST_COMMAND      ""
    INSTALL_COMMAND   ""
    BUILD_IN_SOURCE   ON
    LOG_BUILD         ON
)

add_dependencies(${PROJECT_NAME} ${MINI3D_NAME})

target_include_directories(${PROJECT_NAME} PRIVATE
    "${PROJECT_SOURCE_DIR}/${MINI3D_NAME}/mini3d_ffi/"
)

target_link_libraries(${PROJECT_NAME} PRIVATE
    Qt${QT_VERSION_MAJOR}::Widgets
    debug "${PROJECT_SOURCE_DIR}/${MINI3D_NAME}/target/debug/${MINI3D_NAME}.dll.lib"
    optimized "${PROJECT_SOURCE_DIR}/${MINI3D_NAME}/target/release/${MINI3D_NAME}.dll.lib"
)

set_target_properties(${PROJECT_NAME} PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

install(TARGETS ${PROJECT_NAME}
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(${PROJECT_NAME})
endif()
