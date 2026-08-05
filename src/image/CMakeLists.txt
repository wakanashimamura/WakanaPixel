qt_add_library(wakana_pixel_image STATIC
  image_document.cpp
)

target_link_libraries(wakana_pixel_image PUBLIC
  Qt6::Core
  Qt6::Gui
  wakana_pixel_includes
)