cmake_minimum_required(VERSION 3.21)

project(wakana_pixel VERSION 1.0.0 LANGUAGES CXX)

find_package(Qt6 6.5 REQUIRED COMPONENTS Core Gui Widgets)

qt_standard_project_setup()

add_library(wakana_pixel_includes INTERFACE)

target_include_directories(wakana_pixel_includes INTERFACE 
  "${CMAKE_CURRENT_SOURCE_DIR}/src"
)

add_subdirectory(src/ui)

qt_add_executable(wakana_pixel
  WIN32 
  MACOSX_BUNDLE
  src/main.cpp
)

target_link_libraries(wakana_pixel PRIVATE
  wakana_pixel_includes
  wakana_pixel_ui
)
