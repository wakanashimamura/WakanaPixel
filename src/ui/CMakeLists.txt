qt_add_library(wakana_pixel_ui STATIC
  image_view.cpp
  image_view.h

  main_window.cpp
  main_window.h
  main_window.ui
)

target_link_libraries(wakana_pixel_ui PUBLIC
  Qt6::Core
  Qt6::Gui
  Qt6::Widgets
  wakana_pixel_includes
)