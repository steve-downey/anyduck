#include <anyduck/anyduck.h>
#include <anyduck/anyduck_hiddenduck.h>

#include <benchmark/benchmark.h>

#include <sstream>

BENCHMARK_MAIN();

using namespace anyduck;

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

static void Benchmark_Construct_AnyDuck(benchmark::State& state) {
    Duck d;
    for (auto _ : state) {
        AnyDuck a(d);
        benchmark::DoNotOptimize(a.quack(1));
    }
}
BENCHMARK(Benchmark_Construct_AnyDuck);

static void Benchmark_Construct_AnyDuck_LValue(benchmark::State& state) {
    for (auto _ : state) {
        Duck d;
        AnyDuck a(d);
        benchmark::DoNotOptimize(a.quack(1));
    }
}
BENCHMARK(Benchmark_Construct_AnyDuck_LValue);

static void Benchmark_Construct_AnyDuck_Temp(benchmark::State& state) {
    for (auto _ : state) {
        AnyDuck am(Mallard{});
        benchmark::DoNotOptimize(am.quack(2));
    }
}
BENCHMARK(Benchmark_Construct_AnyDuck_Temp);

static void Benchmark_Construct_HiddenAnyDuck_LValue(benchmark::State& state) {
    for (auto _ : state) {
        HiddenMallard d;
        AnyDuck a(d);
        benchmark::DoNotOptimize(a.quack(2));
    }
}
BENCHMARK(Benchmark_Construct_HiddenAnyDuck_LValue);

static void Benchmark_Construct_HiddenAnyDuck_Temp(benchmark::State& state) {
    for (auto _ : state) {
        AnyDuck am(HiddenMallard{});
        benchmark::DoNotOptimize(am.quack(2));
    }
}
BENCHMARK(Benchmark_Construct_HiddenAnyDuck_Temp);
