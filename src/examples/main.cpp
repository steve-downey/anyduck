#include <anyduck/anyduck.h>

#include <iostream>

class Duck {
  public:
    int quack(int length) const {
        std::cout << "Duck: " << length << '\n';
        return length;
    }
};

class Mallard {
  public:
    int quack(int length) const;
};

int Mallard::quack(int length) const {
    std::cout << "Mallard: " << 2 * length << '\n';
    return length * 2;
}

int test(Mallard& mallard) {
    anyduck::AnyDuck a(mallard);
    return a.quack(1);
}

int test(anyduck::AnyDuck const& a) {
    return a.quack(1);
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
