qt_add_library(wakana_pixel_ui STATIC
  controls/crop_position_selector.cpp
  controls/crop_position_selector.h

  controls/image_size_selector.cpp
  controls/image_size_selector.h

  controls/resize_mode_selector.cpp
  controls/resize_mode_selector.h

  controls/rounding_mode_selector.cpp
  controls/rounding_mode_selector.h

  controls/slider_spin_box.cpp
  controls/slider_spin_box.h

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