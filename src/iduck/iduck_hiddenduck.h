// iduck_hiddenduck.h                                               -*-C++-*-
#ifndef INCLUDED_IDUCK_HIDDENDUCK
#define INCLUDED_IDUCK_HIDDENDUCK
#include <iduck/iduck.h>

namespace iduck {

class HiddenMallard  : public Duck {
  public:
    HiddenMallard();
    ~HiddenMallard();
    int quack(int length) const;
};
}

#endif
