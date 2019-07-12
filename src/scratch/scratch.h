// scratch.h                                                       -*-C++-*-
#ifndef INCLUDED_SCRATCH
#define INCLUDED_SCRATCH

#include <memory>
#include <variant>
#include <vector>
#include <any>
#include <type_traits>

namespace scratch {

class AnyDuck {
    std::any duck_;
    using quackfn = void (*)(std::any const&, int);
    quackfn quack_;

  public:
    AnyDuck(AnyDuck const&) = default;
    AnyDuck(AnyDuck&) = default;
    AnyDuck() = default;

    template <typename Duck>
    AnyDuck(Duck&& duck)
        : duck_(std::forward<Duck>(duck)),
          quack_([](std::any const& d, int i) {
              return std::any_cast<std::remove_reference_t<Duck>>(&d)->quack(
                  i);
          }) {}

    void quack(int length) const { return quack_(this->duck_, length); }
};

} // namespace scratch

#endif
