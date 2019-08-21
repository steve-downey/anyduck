// anyduck.h                                                       -*-C++-*-
#ifndef INCLUDED_ANYDUCK
#define INCLUDED_ANYDUCK

#include <memory>
#include <variant>
#include <vector>
#include <any>
#include <type_traits>

namespace anyduck {

class AnyDuck {
    struct concept_t {
        using quackfn = int (*)(std::any const&, int);
        quackfn quack_;

        concept_t(quackfn quack) : quack_(quack) {}
    };

    std::any duck_;
    concept_t model_;

  public:
    AnyDuck(AnyDuck const&) = default;
    AnyDuck(AnyDuck&) = default; // Make sure not to catch & in template
    AnyDuck() = default;

    template <typename Duck>
    AnyDuck(Duck&& duck)
        : duck_(std::forward<Duck>(duck)),
          model_([](std::any const& d, int i) {
                    return std::any_cast<std::remove_reference_t<Duck>>(&d)->quack(
                        i);
                }) {}

    int quack(int length) const { return model_.quack_(this->duck_, length); }
};

class AnyDuckVtbl {
    struct concept_t {
        using quackfn = int (*)(std::any const&, int);
        quackfn quack_;

        concept_t(quackfn quack) : quack_(quack) {}
    };

    template <typename Duck>
    concept_t* getVtbl() {
        static concept_t vtbl(
            [](std::any const& d, int i) {
                return std::any_cast<std::remove_reference_t<Duck>>(&d)->quack(
                    i);
            });
        return &vtbl;
    }
    std::any duck_;
    concept_t* vtbl_;

  public:
    AnyDuckVtbl(AnyDuckVtbl const&) = default;
    AnyDuckVtbl(AnyDuckVtbl&) = default; // Make sure not to catch & in template
    AnyDuckVtbl() = default;

    template <typename Duck>
    AnyDuckVtbl(Duck&& duck)
    : duck_(std::forward<Duck>(duck)),
      vtbl_(getVtbl<Duck>()) {}

    int quack(int length) const { return vtbl_->quack_(this->duck_, length); }
};

} // namespace anyduck

#endif
