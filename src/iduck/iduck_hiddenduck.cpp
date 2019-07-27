#include <iduck/iduck_hiddenduck.h>

using namespace iduck;

HiddenMallard::HiddenMallard() {}
HiddenMallard::~HiddenMallard() {}

int HiddenMallard::quack(int length) const {
    return 3*length;
}
