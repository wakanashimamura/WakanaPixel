qt_add_library(wakana_pixel_processing STATIC
  resize.cpp
  resize_utils.cpp
)

target_link_libraries(wakana_pixel_processing PUBLIC
  Qt6::Core
  Qt6::Gui
  wakana_pixel_includes
  wakana_pixel_algorithms
)