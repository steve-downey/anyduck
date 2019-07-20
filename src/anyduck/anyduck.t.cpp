#include <anyduck/anyduck.h>
#include <anyduck/anyduck_hiddenduck.h>

#define CATCH_CONFIG_ENABLE_BENCHMARKING
#include <catch2/catch.hpp>

#include <iostream>

using namespace anyduck;


TEST_CASE("TestCatch2") {
    SECTION("Test Catch2") {
        REQUIRE(true);
    }
}

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

int test(Mallard& mallard) {
    AnyDuck a(mallard);
    return a.quack(1);
}

int test(AnyDuck a) {
    return a.quack(1);
}

TEST_CASE("AnyduckTest") {
    SECTION("Breathing") {
        Duck d;
        AnyDuck a(d);
        CHECK(a.quack(1) == 1);

        const Duck cd;
        AnyDuck ca(cd);
        CHECK(ca.quack(1) == 1);

        AnyDuck am(Mallard{});
        CHECK(am.quack(2) == 4);

        CHECK(test(Mallard{}) == 2);
        CHECK(test(a) == 1);
    }

    SECTION("Benchmark") {
        Duck d;
        AnyDuck a(d);

        BENCHMARK("AnyDuck Quack") {
            return a.quack(1);
        };

        BENCHMARK("Construct AnyDuck") {
            AnyDuck a(d);
            return a.quack(1);
        };

        BENCHMARK("Construct AnyDuck LValue") {
            Duck d;
            AnyDuck a(d);
            return a.quack(2);
        };

        BENCHMARK("Construct AnyDuck Temp") {
            AnyDuck am(Mallard{});
            return am.quack(2);
        };

        BENCHMARK("Construct Hidden AnyDuck LValue") {
            HiddenMallard d;
            AnyDuck a(d);
            return a.quack(2);
        };

        BENCHMARK("Construct Hidden AnyDuck Temp") {
            AnyDuck am(HiddenMallard{});
            return am.quack(2);
        };
        }

}
