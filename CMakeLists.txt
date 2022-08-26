cmake_minimum_required(VERSION 3.5)

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
    qt_add_executable(${PROJECT_NAME}
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

set(MINI3D_PROJECT mini3d-project)
set(MINI3D_LIB mini3d)
set(MINI3D_DIR mini3d)
if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(MINI3D_TARGET debug)
    set(MINI3D_BUILD_COMMAND cargo build)
else()
    set(MINI3D_TARGET release)
    set(MINI3D_BUILD_COMMAND cargo build --release)
endif()
set(MINI3D_LIB_PRODUCT "${PROJECT_SOURCE_DIR}/${MINI3D_DIR}/target/${MINI3D_TARGET}/${CMAKE_SHARED_LIBRARY_PREFIX}${MINI3D_LIB}${CMAKE_SHARED_LIBRARY_SUFFIX}")
include(ExternalProject)
ExternalProject_Add(
    ${MINI3D_PROJECT}
    BUILD_BYPRODUCTS  ${MINI3D_LIB_PRODUCT}
    GIT_REPOSITORY    "https://github.com/thomasbechet/mini3d.git"
    BUILD_COMMAND     ${MINI3D_BUILD_COMMAND}
    SOURCE_DIR        "${PROJECT_SOURCE_DIR}/${MINI3D_DIR}"
    UPDATE_COMMAND    ""
    CONFIGURE_COMMAND ""
    INSTALL_COMMAND   ""
    TEST_COMMAND      ""
    INSTALL_COMMAND   ""
    BUILD_IN_SOURCE   ON
    LOG_BUILD         ON
)

add_library(${MINI3D_LIB} SHARED IMPORTED)
set_target_properties(${MINI3D_LIB} PROPERTIES
    IMPORTED_LOCATION ${MINI3D_LIB_PRODUCT}
)

add_dependencies(${PROJECT_NAME} ${MINI3D_LIB})

target_include_directories(${PROJECT_NAME} PRIVATE
    "${PROJECT_SOURCE_DIR}/${MINI3D_DIR}/mini3d_ffi/"
)

target_link_libraries(${PROJECT_NAME} PRIVATE
    Qt${QT_VERSION_MAJOR}::Widgets
    ${MINI3D_LIB_PRODUCT}
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
