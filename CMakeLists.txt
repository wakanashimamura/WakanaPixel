cmake_minimum_required(VERSION 3.20)

# ========================
# Project Setup
# ========================

project(WakanaPixel VERSION 0.0.2 LANGUAGES CXX)

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
  src/main.cpp
  src/wsmainwindow.cpp
  src/wsgraphicsview.cpp
)

set(HEADER
  include/wsmainwindow.h
  include/wsgraphicsview.h
  include/wsimage.h
)

set(UI
  ui/wsmainwindow.ui
)

set(RESOURCES
  resources/resources.qrc
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
    Qt::Core
    Qt::Widgets
)

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
