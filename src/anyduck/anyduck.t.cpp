#include <anyduck/anyduck.h>

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
    void quack(int length) const {std::cout << "Duck: " << length << '\n';}
};

class Mallard {
  public:
    void quack(int length) const;
};

void Mallard::quack(int length) const {
    std::cout << "Mallard: " << length << '\n';
}
void test(Mallard& mallard) {
    AnyDuck a(mallard);
    a.quack(1);
}

void test(AnyDuck a) {
    a.quack(1);
}

TEST_CASE("AnyduckTest") {
    SECTION("Breathing") {
        Duck d;
        AnyDuck a(d);
        a.quack(1);

        const Duck cd;
        AnyDuck ca(cd);
        ca.quack(1);

        AnyDuck am(Mallard{});
        am.quack(2);

        test(Mallard{});
        test(a);
    }
}
