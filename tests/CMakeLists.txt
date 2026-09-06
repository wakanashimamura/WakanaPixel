include(FetchContent)

FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG v1.18.0
)

FetchContent_MakeAvailable(googletest)

enable_testing()

qt_add_executable(unit_tests
  rgb_test.cpp
)

target_link_libraries(unit_tests PRIVATE
  GTest::gtest_main
  wakana_pixel_includes
  wakana_pixel_image
)
