cmake_minimum_required(VERSION 3.19)
project(WakanaPixel VERSION 0.0.1 LANGUAGES CXX)

set(CMAKE_AUTORCC ON)

find_package(Qt6 6.5 REQUIRED COMPONENTS Core Widgets)

qt_standard_project_setup()

set(CMAKE_AUTOUIC_SEARCH_PATHS ui)

qt_add_executable(${PROJECT_NAME}
  WIN32 MACOSX_BUNDLE
  resources/resources.qrc
  src/main.cpp
  
  src/wsmainwindow.cpp
  include/wsmainwindow.h
  ui/wsmainwindow.ui

  src/wsgraphicsview.cpp
  include/wsgraphicsview.h
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
