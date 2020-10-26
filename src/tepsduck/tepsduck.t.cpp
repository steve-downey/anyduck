#include <tepsduck/tepsduck.h>
#include <tepsduck/tepsduck_hiddenduck.h>

#define CATCH_CONFIG_ENABLE_BENCHMARKING
#include <catch2/catch_all.hpp>

#include <iostream>

using namespace tepsduck;


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
    TEPSDuck a(mallard);
    return a.quack(1);
}

int test(TEPSDuck const& a) {
    return a.quack(1);
}

TEST_CASE("TEPSDuckTest") {
    SECTION("Breathing") {
        Duck d;
        TEPSDuck a(d);
        CHECK(a.quack(1) == 1);

        const Duck cd;
        TEPSDuck ca(cd);
        CHECK(ca.quack(1) == 1);

        TEPSDuck am(Mallard{});
        CHECK(am.quack(2) == 4);

        CHECK(test(Mallard{}) == 2);
        CHECK(test(a) == 1);
    }

    SECTION("Benchmark") {
        Duck d;
        TEPSDuck a(d);

        BENCHMARK("TEPSDuck Quack") {
            return a.quack(1);
        };

        BENCHMARK("Construct TEPSDuck") {
            TEPSDuck a(d);
            return a.quack(1);
        };

        BENCHMARK("Construct TEPSDuck LValue") {
            Duck d;
            TEPSDuck a(d);
            return a.quack(2);
        };

        BENCHMARK("Construct TEPSDuck Temp") {
            TEPSDuck am(Mallard{});
            return am.quack(2);
        };

        BENCHMARK("Construct Hidden TEPSDuck LValue") {
            HiddenMallard d;
            TEPSDuck a(d);
            return a.quack(2);
        };

        BENCHMARK("Construct Hidden TEPSDuck Temp") {
            TEPSDuck am(HiddenMallard{});
            return am.quack(2);
        };
    }

}
