// tepsduck.h                                                         -*-C++-*-
#ifndef INCLUDED_TEPSDUCK
#define INCLUDED_TEPSDUCK

#include <memory>

//@PURPOSE:
//
//@CLASSES:
//
//@AUTHOR: Steve Downey (sdowney)
//
//@DESCRIPTION:


namespace tepsduck {

class TEPSDuck {
    struct concept_t {
        virtual ~concept_t() {}
        virtual int quack(int i) const = 0;
    };

    template <typename T>
    struct model_t : public concept_t {
        model_t() = default;
        model_t(const T& v) : m_data(v) {}
        model_t(T&& v) : m_data(std::move(v)) {}

        int quack(int i) const { return m_data.quack(i); }

        T m_data;
    };
  public:
    TEPSDuck() = default;

    TEPSDuck(const TEPSDuck&) = delete;
    TEPSDuck(TEPSDuck&&) = default;

    template <typename T>
    TEPSDuck(T&& impl)
    : m_impl(new model_t<std::decay_t<T>>(std::forward<T>(impl))) {}

    TEPSDuck& operator=(const TEPSDuck&) = delete;
    TEPSDuck& operator=(TEPSDuck&&) = default;

    template <typename T>
    TEPSDuck& operator=(T&& impl) {
        m_impl.reset(new model_t<std::decay_t<T>>(std::forward<T>(impl)));
        return *this;
    }

    int quack(int i) const { return m_impl->quack(i); }

  private:
    std::unique_ptr<concept_t> m_impl;
};

}



#endif
