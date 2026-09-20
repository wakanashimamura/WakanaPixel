#include <benchmark/benchmark.h>

// 1. The Function
static void BM_MyBencmark(benchmark::State& state) {
  // Setup code (Not timed)
  // We can construct objects here

  // 2. The Measurement Loop
  for (auto _ : state) {
    state.PauseTiming();
    // This code is not timed
    state.ResumeTiming();

    // This code is timed

    // Prevent the result from being optimized away
    int result = 0;
    benchmark::DoNotOptimize(result);
  }
}

// 3. Register the function as a benchmark
BENCHMARK(BM_MyBencmark);