#include <benchmark/benchmark.h>

#include "solution.h"

std::vector<std::string> generate_vector(int n)
{
    std::vector<std::string> vector;
    for(int i = 0; i < n; ++i)
    {
        vector.push_back(std::to_string(i));
    }

    return vector;
}

static void BM_Solution(benchmark::State &state)
{
    auto n{ static_cast<int>(state.range(0)) };
    auto v{ generate_vector(n) };

    // Perform setup here
    for(auto _ : state)
    {
        Solution solution;
        benchmark::DoNotOptimize(solution.cal_points(v));
    }

    state.SetComplexityN(n);
}

// This will start with an input size of 64 and double the size until it reaches 4096.
BENCHMARK(BM_Solution)->RangeMultiplier(2)->Range(64, 4096)->Complexity();
