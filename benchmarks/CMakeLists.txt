include(FetchContent)

set(BENCHMARK_ENABLE_TESTING OFF CACHE BOOL "" FORCE)
set(BENCHMARK_ENABLE_INSTALL OFF CACHE BOOL "" FORCE)

FetchContent_Declare(
  googlebenchmark
  GIT_REPOSITORY https://github.com/google/benchmark.git
  GIT_TAG v1.9.5
)

FetchContent_MakeAvailable(googlebenchmark)

qt_add_executable(benchmarks
  main.cpp
)

target_link_libraries(benchmarks PRIVATE
  benchmark::benchmark
  benchmark::benchmark_main
  Qt6::Core
  wakana_pixel_includes
)
