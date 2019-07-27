#include <tepsduck/tepsduck_hiddenduck.h>

using namespace tepsduck;

HiddenMallard::HiddenMallard() {}
HiddenMallard::~HiddenMallard() {}

int HiddenMallard::quack(int length) const {
    return 3*length;
}
