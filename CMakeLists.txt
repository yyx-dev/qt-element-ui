cmake_minimum_required(VERSION 4.0)

project(qt-element-ui VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS TRUE)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

#set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

#set(CMAKE_BUILD_TYPE Release)

find_package(Qt6 COMPONENTS Core Widgets Gui Svg LinguistTools QUIET)
if(Qt6_FOUND)
    set(QT_LIBRARIES Qt6::Core Qt6::Widgets Qt6::Gui Qt6::Svg)
    message(STATUS "Found Qt6, using C++ latest/23")
else()
    find_package(Qt5 COMPONENTS Core Widgets Gui Svg LinguistTools REQUIRED)
    set(QT_LIBRARIES Qt5::Core Qt5::Widgets Qt5::Gui Qt5::Svg)
    message(STATUS "Qt6 not found, using Qt5 fallback")
endif()

file(GLOB_RECURSE HEADERS
    components/*.h
    components/private/*.h
    example/*.h
    gallery/*.h
)

file(GLOB_RECURSE SOURCES
    components/*.cpp
    components/private/*.cpp
    example/*.cpp
    gallery/*.cpp
)

file(GLOB FORMS
    example/*.ui
)

file(GLOB RESOURCES
    resources/*.qrc
    gallery/*.qrc
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
    ${CMAKE_CURRENT_SOURCE_DIR}/components/private
    ${CMAKE_CURRENT_SOURCE_DIR}/example
    ${CMAKE_CURRENT_SOURCE_DIR}/gallery
)

target_link_libraries(qt-element-ui
    Qt5::Core
    Qt5::Widgets
    Qt5::Gui
    Qt5::Svg
)
target_compile_options(qt-element-uiui INTERFACE
    # GCC
    $<$<AND:$<CXX_COMPILER_ID:GNU>,$<CONFIG:Debug>>:-Wall -Wextra -Wpedantic -O0 -g>
    $<$<AND:$<CXX_COMPILER_ID:GNU>,$<CONFIG:Release>>:-Wall -O3 -DNDEBUG>

    # Clang
    $<$<AND:$<CXX_COMPILER_ID:Clang>,$<CONFIG:Debug>>:-Wall -Wextra -Wpedantic -O0 -g>
    $<$<AND:$<CXX_COMPILER_ID:Clang>,$<CONFIG:Release>>:-Wall -O3 -DNDEBUG>

    # MSVC
    $<$<AND:$<CXX_COMPILER_ID:MSVC>,$<CONFIG:Debug>>:/W4 /Od /Zi /EHsc>
    $<$<AND:$<CXX_COMPILER_ID:MSVC>,$<CONFIG:Release>>:/O2 /DNDEBUG /EHsc>

    # Clang-cl
    $<$<AND:$<CXX_COMPILER_ID:Clang>,$<CXX_COMPILER_FRONTEND_VARIANT:MSVC>,$<CONFIG:Debug>>:/EHsc /Zi /W4>
    $<$<AND:$<CXX_COMPILER_ID:Clang>,$<CXX_COMPILER_FRONTEND_VARIANT:MSVC>,$<CONFIG:Release>>:/EHsc /O3 /DNDEBUG>

)
if(WIN32)
    target_link_libraries(qt-element-ui gdi32 dwmapi)
endif()

if(Qt6_FOUND)
    # Qt6 推荐使用新的命令，它会自动处理 .ts 到 .qm 的转换
    qt6_add_translation(QM_FILES ${TRANSLATIONS})
else()
    # Qt5 使用旧的命令
    qt5_add_translation(QM_FILES ${TRANSLATIONS})
endif()