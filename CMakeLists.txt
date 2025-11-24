cmake_minimum_required(VERSION 4.0)

project(qt-element-ui VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS TRUE)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_BUILD_TYPE Release)

find_package(Qt5 COMPONENTS Core Widgets Gui Svg LinguistTools REQUIRED)

file(GLOB_RECURSE HEADERS
    components/*.h
    components/deprecated/*.h
    examples/*.h
    gallery/*.h
)

file(GLOB_RECURSE SOURCES
    components/*.cpp
    components/deprecated/*.cpp
    examples/*.cpp
    gallery/*.cpp
)

file(GLOB FORMS
    examples/*.ui
)

file(GLOB RESOURCES
    resources/*.qrc
)

file(GLOB TRANSLATIONS
    resources/locales/*.ts
)

add_executable(qt-element-ui
    ${HEADERS}
    ${SOURCES}
    ${FORMS}
    ${RESOURCES}
)

target_include_directories(qt-element-ui PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/components
    ${CMAKE_CURRENT_SOURCE_DIR}/components/deprecated
    ${CMAKE_CURRENT_SOURCE_DIR}/examples
    ${CMAKE_CURRENT_SOURCE_DIR}/gallery
)

target_link_libraries(qt-element-ui
    Qt5::Core
    Qt5::Widgets
    Qt5::Gui
    Qt5::Svg
)

qt5_add_translation(QM_FILES ${TRANSLATIONS})