#include <tepsduck/tepsduck.h>
#include <tepsduck/tepsduck_hiddenduck.h>

#include <benchmark/benchmark.h>

#include <sstream>

BENCHMARK_MAIN();

using namespace tepsduck;

class Duck {
  public:
    int quack(int length) const {return length;}
};

class Mallard {
  public:
    int quack(int length) const;
};

int Mallard::quack(int length) const {
    return 2*length;
}

static void Benchmark_Construct_TEPSDuck(benchmark::State& state) {
    Duck d;
    for (auto _ : state) {
        TEPSDuck a(d);
        benchmark::DoNotOptimize(a.quack(1));
    }
}
BENCHMARK(Benchmark_Construct_TEPSDuck);

static void Benchmark_Construct_TEPSDuck_LValue(benchmark::State& state) {
    for (auto _ : state) {
        Duck d;
        TEPSDuck a(d);
        benchmark::DoNotOptimize(a.quack(1));
    }
}
BENCHMARK(Benchmark_Construct_TEPSDuck_LValue);

static void Benchmark_Construct_TEPSDuck_Temp(benchmark::State& state) {
    for (auto _ : state) {
        TEPSDuck am(Mallard{});
        benchmark::DoNotOptimize(am.quack(2));
    }
}
BENCHMARK(Benchmark_Construct_TEPSDuck_Temp);

static void Benchmark_Construct_HiddenTEPSDuck_LValue(benchmark::State& state) {
    for (auto _ : state) {
        HiddenMallard d;
        TEPSDuck a(d);
        benchmark::DoNotOptimize(a.quack(2));
    }
}
BENCHMARK(Benchmark_Construct_HiddenTEPSDuck_LValue);

static void Benchmark_Construct_HiddenTEPSDuck_Temp(benchmark::State& state) {
    for (auto _ : state) {
        TEPSDuck am(HiddenMallard{});
        benchmark::DoNotOptimize(am.quack(2));
    }
}
BENCHMARK(Benchmark_Construct_HiddenTEPSDuck_Temp);
