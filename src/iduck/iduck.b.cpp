#include <iduck/iduck.h>
#include <iduck/iduck_hiddenduck.h>

#include <benchmark/benchmark.h>

#include <sstream>

BENCHMARK_MAIN();

using namespace iduck;

class ADuck : public Duck {
  public:
    int quack(int length) const {return length;}
};

class Mallard  : public Duck {
  public:
    int quack(int length) const;
};

int Mallard::quack(int length) const {
    return 2*length;
}

static void Benchmark_Construct_IDuck(benchmark::State& state) {
    ADuck d;
    for (auto _ : state) {
        IDuck a(d);
        benchmark::DoNotOptimize(a.quack(1));
    }
}
BENCHMARK(Benchmark_Construct_IDuck);

static void Benchmark_Construct_IDuck_LValue(benchmark::State& state) {
    for (auto _ : state) {
        ADuck d;
        IDuck a(d);
        benchmark::DoNotOptimize(a.quack(1));
    }
}
BENCHMARK(Benchmark_Construct_IDuck_LValue);

static void Benchmark_Construct_IDuck_Temp(benchmark::State& state) {
    for (auto _ : state) {
        IDuck am(Mallard{});
        benchmark::DoNotOptimize(am.quack(2));
    }
}
BENCHMARK(Benchmark_Construct_IDuck_Temp);

static void Benchmark_Construct_HiddenIDuck_LValue(benchmark::State& state) {
    for (auto _ : state) {
        HiddenMallard d;
        IDuck a(d);
        benchmark::DoNotOptimize(a.quack(2));
    }
}
BENCHMARK(Benchmark_Construct_HiddenIDuck_LValue);

static void Benchmark_Construct_HiddenIDuck_Temp(benchmark::State& state) {
    for (auto _ : state) {
        IDuck am(HiddenMallard{});
        benchmark::DoNotOptimize(am.quack(2));
    }
}
BENCHMARK(Benchmark_Construct_HiddenIDuck_Temp);
