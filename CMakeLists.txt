cmake_minimum_required(VERSION 3.14)

project(editorQGadget LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 COMPONENTS Core Gui Widgets REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Core Gui Widgets REQUIRED)

add_executable(editorQGadget
  main.cpp
  editorqgadget.cpp
  elements/checkbox.cpp
  elements/combobox.cpp
  elements/doublespinbox.cpp
  elements/spinbox.cpp
  elements/qgadgetfactory.cpp
  player.h
  playertype.h
  p2d.h
)
target_link_libraries(editorQGadget
    Qt${QT_VERSION_MAJOR}::Core
    Qt${QT_VERSION_MAJOR}::Gui
    Qt${QT_VERSION_MAJOR}::Widgets
)
