qt_add_library(wakana_pixel_application STATIC
  processing_controller.cpp
  processing_controller.h
)

target_link_libraries(wakana_pixel_application PUBLIC
  Qt6::Core
  Qt6::Gui
  wakana_pixel_includes
  wakana_pixel_image
  wakana_pixel_processing
)