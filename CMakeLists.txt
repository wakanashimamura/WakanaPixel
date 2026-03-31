cmake_minimum_required(VERSION 3.16)

# ========================
# Project Setup
# ========================

project(WakanaPixel VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# ========================
# Qt
# ========================

find_package(Qt6 6.5 REQUIRED COMPONENTS Core Widgets)

qt_standard_project_setup()

set(CMAKE_AUTORCC ON)

set(CMAKE_AUTOUIC_SEARCH_PATHS ui)

# ========================
# Source Files
# ========================

set(SOURCES
  src/main.cc

  src/model/image.cc

  src/ui/graphics_view.cc
  src/ui/main_window.cc
)

set(HEADER
  include/ui/graphics_view.h
  include/ui/main_window.h
)

set(UI
  ui/main_window.ui
)

set(RESOURCES
)

# ========================
# Executable
# ========================

qt_add_executable(${PROJECT_NAME}
  WIN32 
  MACOSX_BUNDLE
  ${SOURCES}
  ${HEADER}
  ${UI}
  ${RESOURCES}
)

target_include_directories(${PROJECT_NAME} PRIVATE include)

target_link_libraries(${PROJECT_NAME}
  PRIVATE
    Qt6::Core
    Qt6::Widgets
)

set(CMAKE_INSTALL_PREFIX "${CMAKE_CURRENT_SOURCE_DIR}" CACHE PATH "Install path" FORCE)

include(GNUInstallDirs)

install(TARGETS ${PROJECT_NAME}
  BUNDLE  DESTINATION .
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

qt_generate_deploy_app_script(
  TARGET ${PROJECT_NAME}
  OUTPUT_SCRIPT deploy_script
  NO_UNSUPPORTED_PLATFORM_ERROR
)
install(SCRIPT ${deploy_script})
