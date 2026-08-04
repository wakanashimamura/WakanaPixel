qt_add_library(wakana_pixel_ui STATIC
  main_window.cpp
  main_window.h
  main_window.ui
)

target_link_libraries(wakana_pixel_ui PUBLIC
  Qt6::Widgets
  Qt6::Gui
  wakana_pixel_includes
)