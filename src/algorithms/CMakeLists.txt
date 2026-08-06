qt_add_library(wakana_pixel_algorithms STATIC
  scale/nearest_neighbor_scaler.cpp
)

target_link_libraries(wakana_pixel_algorithms PUBLIC
  Qt6::Core
  Qt6::Gui
  wakana_pixel_includes
)