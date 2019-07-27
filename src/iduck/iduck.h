// iduck.h                                                       -*-C++-*-
#ifndef INCLUDED_IDUCK
#define INCLUDED_IDUCK

#include <memory>
#include <variant>
#include <vector>
#include <any>
#include <type_traits>

namespace iduck {
class Duck {
  public:
    virtual ~Duck();
    virtual int quack(int length) const = 0;

};

class IDuck {
    std::unique_ptr<Duck> duck_;

  public:
    IDuck(IDuck const&) = default;
    IDuck(IDuck&) = default;
    IDuck() = default;

    template <typename D>
    IDuck(D&& duck) :
    duck_(new std::decay_t<D>(std::forward<D>(duck)))
    {}

    int quack(int length) const { return this->duck_->quack(length); }
};

} // namespace iduck

#endif
