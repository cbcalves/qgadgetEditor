cmake_minimum_required(VERSION 3.16)

project(editorQGadget LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(MSVC)
  set(COMPILE_WARNS /W4 /WX)
else()
  set(COMPILE_WARNS -Wall -Wextra -pedantic)
endif()

find_package(QT NAMES Qt6 Qt5 COMPONENTS Core Gui Widgets REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Core Gui Widgets REQUIRED)

add_executable(editorQGadget
  main.cpp
  editorqgadget.cpp
  elements/checkbox.cpp
  elements/combobox.cpp
  elements/doublespinbox.cpp
  elements/ptrformlayout.cpp
  elements/spinbox.cpp
  elements/qgadgetfactory.cpp
  players/player.h
  players/playerbuilder.cpp
  players/playertype.h
  players/p2d.h
)
target_link_libraries(editorQGadget
    Qt${QT_VERSION_MAJOR}::Core
    Qt${QT_VERSION_MAJOR}::Gui
    Qt${QT_VERSION_MAJOR}::Widgets
)
