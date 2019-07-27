#include <iduck/iduck.h>
#include <iduck/iduck_hiddenduck.h>

#define CATCH_CONFIG_ENABLE_BENCHMARKING
#include <catch2/catch.hpp>

#include <iostream>

using namespace iduck;


TEST_CASE("TestCatch2") {
    SECTION("Test Catch2") {
        REQUIRE(true);
    }
}

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

int test(Mallard& mallard) {
    IDuck a(mallard);
    return a.quack(1);
}

int test(IDuck const& a) {
    return a.quack(1);
}

TEST_CASE("IDuckTest") {
    SECTION("Breathing") {
        ADuck d;
        IDuck a(d);
        CHECK(a.quack(1) == 1);

        const ADuck cd;
        IDuck ca(cd);
        CHECK(ca.quack(1) == 1);

        IDuck am(Mallard{});
        CHECK(am.quack(2) == 4);

        CHECK(test(Mallard{}) == 2);
        CHECK(test(a) == 1);
    }

    SECTION("Benchmark") {
        ADuck d;
        IDuck a(d);

        BENCHMARK("IDuck Quack") {
            return a.quack(1);
        };

        BENCHMARK("Construct IDuck") {
            IDuck a(d);
            return a.quack(1);
        };

        BENCHMARK("Construct IDuck LValue") {
            ADuck d;
            IDuck a(d);
            return a.quack(2);
        };

        BENCHMARK("Construct IDuck Temp") {
            IDuck am(Mallard{});
            return am.quack(2);
        };

        BENCHMARK("Construct Hidden IDuck LValue") {
            HiddenMallard d;
            IDuck a(d);
            return a.quack(2);
        };

        BENCHMARK("Construct Hidden IDuck Temp") {
            IDuck am(HiddenMallard{});
            return am.quack(2);
        };
        }

}
