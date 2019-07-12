#include <scratch/scratch.h>

#include <gtest/gtest.h>

using namespace scratch;

TEST(ScratchTest, TestGTest) {
    ASSERT_EQ(1, 1);
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

TEST(ScratchTest, Breathing) {
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
