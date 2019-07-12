#include <anyduck/anyduck.h>

#include <iostream>

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
    anyduck::AnyDuck a(mallard);
    a.quack(1);
}

void test(anyduck::AnyDuck const& a) {
    a.quack(1);
}


int main(int /*argc*/, char** /*argv*/)
{
    using namespace anyduck;
    Duck d;
    anyduck::AnyDuck a(d);
    a.quack(1);

    // const Duck cd;
    // anyduck::AnyDuck ca(cd);
    // ca.quack(1);

    // anyduck::AnyDuck am(Mallard{});
    // am.quack(2);

    // test(Mallard{});
    // test(a);

    Duck d2;
    d2.quack(2);
}
